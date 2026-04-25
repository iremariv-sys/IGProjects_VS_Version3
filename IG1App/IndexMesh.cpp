#include "IndexMesh.h"
#include <cassert>
#include <cmath>
#include <limits>

#include <glm/gtc/constants.hpp>

using namespace std;
using namespace glm;

constexpr GLuint NONE = numeric_limits<GLuint>::max();

IndexMesh::IndexMesh()
	: Mesh()
	, mIBO(NONE)
{
}

IndexMesh::~IndexMesh()
{
	unload();
}

void IndexMesh::draw() const
{
	glDrawElements(
		mPrimitive,
		GLsizei(vIndexes.size()),
		GL_UNSIGNED_INT,
		nullptr);
}

void IndexMesh::load()
{
	Mesh::load();

	assert(mIBO == NONE);

	if (mVAO != NONE && !vIndexes.empty()) {
		glBindVertexArray(mVAO);

		glGenBuffers(1, &mIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			vIndexes.size() * sizeof(GLuint),
			vIndexes.data(),
			GL_STATIC_DRAW);

		glBindVertexArray(0);
	}
}

void IndexMesh::unload()
{
	if (mIBO != NONE) {
		glDeleteBuffers(1, &mIBO);
		mIBO = NONE;
	}

	Mesh::unload();
}


IndexMesh* IndexMesh::generateByRevolution(
	const std::vector<glm::vec2>& profile,
	GLuint nSamples,
   GLfloat angleMax,
	bool closedProfile)
{
	assert(profile.size() >= 2);
	assert(nSamples >= 1);

	IndexMesh* m = new IndexMesh();
	m->mPrimitive = GL_TRIANGLES;

	const GLuint nProfile = GLuint(profile.size());

  m->vVertices.reserve((nSamples + 1) * nProfile);
	m->vIndexes.reserve(nSamples * (nProfile - 1) * 6);
	m->vTexCoords.reserve((nSamples + 1) * nProfile);

 for (GLuint i = 0; i <= nSamples; ++i) {
		GLfloat ang = angleMax * GLfloat(i) / GLfloat(nSamples);
		GLfloat c = cos(ang);
		GLfloat s = sin(ang);
		GLfloat u = GLfloat(i) / GLfloat(nSamples);

        for (GLuint j = 0; j < nProfile; ++j) {
			const glm::vec2& p = profile[j];
			GLfloat v = (nProfile > 1) ? GLfloat(j) / GLfloat(nProfile - 1) : 0.0f;
			m->vVertices.emplace_back(p.x * c, p.y, p.x * s);
			m->vTexCoords.emplace_back(u, v);
		}
	}

    GLuint segmentCount = closedProfile ? nProfile : (nProfile - 1);
	for (GLuint i = 0; i < nSamples; ++i) {
		GLuint curr = i * nProfile;
     GLuint next = (i + 1) * nProfile;
		//GLuint next = ((i + 1) % nSamples) * nProfile;

         for (GLuint j = 0; j < segmentCount; ++j) {
            GLuint j2 = closedProfile ? (j + 1) % nProfile : j + 1;
			GLuint a = curr + j;
			GLuint b = next + j;
			GLuint c = next + j2;
			GLuint d = curr + j2;

			m->vIndexes.push_back(a);
			m->vIndexes.push_back(b);
			m->vIndexes.push_back(c);

			m->vIndexes.push_back(a);
			m->vIndexes.push_back(c);
			m->vIndexes.push_back(d);
		}
	}

	m->mNumVertices = GLuint(m->vVertices.size());
	m->buildNormalVectors();
	return m;
}

IndexMesh* IndexMesh::generateSphere(GLdouble radius, GLuint nParallel, GLuint nMeridians)
{
	assert(nParallel >= 1);
	assert(nMeridians >= 3);

	std::vector<glm::vec2> profile;
	profile.reserve(nParallel + 1);

	for (GLuint i = 0; i <= nParallel; ++i) {
		GLdouble t = GLdouble(i) / GLdouble(nParallel);
		GLdouble ang = -glm::half_pi<GLdouble>() + t * glm::pi<GLdouble>();
		GLdouble r = radius * cos(ang);
		GLdouble y = radius * sin(ang);
		profile.push_back(glm::vec2(r, y));
	}

	return generateByRevolution(profile, nMeridians);
}


//aparatdo 58
void IndexMesh::buildNormalVectors()
{
	vNormals.assign(vVertices.size(), glm::vec3(0.0f));

	for (size_t i = 0; i + 2 < vIndexes.size(); i += 3) {
		GLuint i0 = vIndexes[i];
		GLuint i1 = vIndexes[i + 1];
		GLuint i2 = vIndexes[i + 2];

		glm::vec3 v0 = vVertices[i0];
		glm::vec3 v1 = vVertices[i1];
		glm::vec3 v2 = vVertices[i2];

		glm::vec3 n(0.0f);

		n.x += (v0.y - v1.y) * (v0.z + v1.z);
		n.y += (v0.z - v1.z) * (v0.x + v1.x);
		n.z += (v0.x - v1.x) * (v0.y + v1.y);

		n.x += (v1.y - v2.y) * (v1.z + v2.z);
		n.y += (v1.z - v2.z) * (v1.x + v2.x);
		n.z += (v1.x - v2.x) * (v1.y + v2.y);

		n.x += (v2.y - v0.y) * (v2.z + v0.z);
		n.y += (v2.z - v0.z) * (v2.x + v0.x);
		n.z += (v2.x - v0.x) * (v2.y + v0.y);

		vNormals[i0] += n;
		vNormals[i1] += n;
		vNormals[i2] += n;
	}

	for (glm::vec3& n : vNormals) {
		float len = glm::length(n);
		if (len > 0.0f)
			n = -n / len;
	}
}
// Apartado 64
IndexMesh* IndexMesh::generateIndexedBox(GLdouble l)
{
	IndexMesh* m = new IndexMesh();
	m->mPrimitive = GL_TRIANGLES;

	GLfloat h = GLfloat(l / 2.0);

	m->vVertices = {
		// front
		{-h, -h,  h}, { h, -h,  h}, { h,  h,  h}, {-h,  h,  h},
		// right
		{ h, -h,  h}, { h, -h, -h}, { h,  h, -h}, { h,  h,  h},
		// back
		{ h, -h, -h}, {-h, -h, -h}, {-h,  h, -h}, { h,  h, -h},
		// left
		{-h, -h, -h}, {-h, -h,  h}, {-h,  h,  h}, {-h,  h, -h},
		// top
		{-h,  h,  h}, { h,  h,  h}, { h,  h, -h}, {-h,  h, -h},
		// bottom
		{-h, -h, -h}, { h, -h, -h}, { h, -h,  h}, {-h, -h,  h}
	};

	m->vIndexes = {
		0, 1, 2,  0, 2, 3,
		4, 5, 6,  4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	m->vNormals = {
		{ 0.0f,  0.0f,  1.0f}, { 0.0f,  0.0f,  1.0f}, { 0.0f,  0.0f,  1.0f}, { 0.0f,  0.0f,  1.0f},
		{ 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f,  0.0f},
		{ 0.0f,  0.0f, -1.0f}, { 0.0f,  0.0f, -1.0f}, { 0.0f,  0.0f, -1.0f}, { 0.0f,  0.0f, -1.0f},
		{-1.0f,  0.0f,  0.0f}, {-1.0f,  0.0f,  0.0f}, {-1.0f,  0.0f,  0.0f}, {-1.0f,  0.0f,  0.0f},
		{ 0.0f,  1.0f,  0.0f}, { 0.0f,  1.0f,  0.0f}, { 0.0f,  1.0f,  0.0f}, { 0.0f,  1.0f,  0.0f},
		{ 0.0f, -1.0f,  0.0f}, { 0.0f, -1.0f,  0.0f}, { 0.0f, -1.0f,  0.0f}, { 0.0f, -1.0f,  0.0f}
	};

	m->mNumVertices = GLuint(m->vVertices.size());
	return m;
}

// Apartado 61
IndexMesh* IndexMesh::generateIndexedBox8(GLdouble l)
{
	IndexMesh* m = new IndexMesh();
	m->mPrimitive = GL_TRIANGLES;

	GLfloat h = GLfloat(l / 2.0);

	m->vVertices = {
		{-h, -h,  h}, // 0
		{ h, -h,  h}, // 1
		{ h,  h,  h}, // 2
		{-h,  h,  h}, // 3
		{-h, -h, -h}, // 4
		{ h, -h, -h}, // 5
		{ h,  h, -h}, // 6
		{-h,  h, -h}  // 7
	};

	m->vIndexes = {
		0, 1, 2,  0, 2, 3, // front
		1, 5, 6,  1, 6, 2, // right
		5, 4, 7,  5, 7, 6, // back
		4, 0, 3,  4, 3, 7, // left
		3, 2, 6,  3, 6, 7, // top
		4, 5, 1,  4, 1, 0  // bottom
	};

	m->mNumVertices = GLuint(m->vVertices.size());
	m->buildNormalVectors();
	return m;
}