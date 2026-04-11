#include "IndexMesh.h"
#include "Material.h"
#include <cassert>
#include <cmath>
#include <limits>

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

//IndexMesh* IndexMesh::generateByRevolution(
//	const std::vector<glm::vec2>& profile,
//	GLuint nSamples,
//	GLfloat angleMax)
//{
//	assert(profile.size() >= 2);
//	assert(nSamples >= 1);
//
//	IndexMesh* m = new IndexMesh();
//	m->mPrimitive = GL_TRIANGLES;
//
//	const GLuint nProfile = GLuint(profile.size());
//
//	// nSamples anillos + 1 para cerrar si angleMax = 2*pi
//	m->vVertices.reserve((nSamples + 1) * nProfile);
//	m->vIndexes.reserve(nSamples * (nProfile - 1) * 6);
//
//	for (GLuint i = 0; i <= nSamples; ++i) {
//		GLfloat ang = angleMax * GLfloat(i) / GLfloat(nSamples);
//		GLfloat c = cos(ang);
//		GLfloat s = sin(ang);
//
//		for (const auto& p : profile) {
//			GLfloat r = p.x;
//			GLfloat y = p.y;
//			m->vVertices.emplace_back(r * c, y, r * s);
//		}
//	}
//
//	for (GLuint i = 0; i < nSamples; ++i) {
//		GLuint curr = i * nProfile;
//		GLuint next = (i + 1) * nProfile;
//
//		for (GLuint j = 0; j + 1 < nProfile; ++j) {
//			GLuint a = curr + j;
//			GLuint b = next + j;
//			GLuint c = next + j + 1;
//			GLuint d = curr + j + 1;
//
//			m->vIndexes.push_back(a);
//			m->vIndexes.push_back(b);
//			m->vIndexes.push_back(c);
//
//			m->vIndexes.push_back(a);
//			m->vIndexes.push_back(c);
//			m->vIndexes.push_back(d);
//		}
//	}
//
//	m->mNumVertices = GLuint(m->vVertices.size());
//	m->buildNormalVectors(); ////
//	
//	return m;
//}

IndexMesh* IndexMesh::generateByRevolution(
	const std::vector<glm::vec2>& profile,
	GLuint nSamples,
	GLfloat angleMax)
{
	assert(profile.size() >= 2);
	assert(nSamples >= 1);

	IndexMesh* m = new IndexMesh();
	m->mPrimitive = GL_TRIANGLES;

	const GLuint nProfile = GLuint(profile.size());

	// 1. Reservar memoria para evitar reasignaciones
	m->vVertices.reserve((nSamples + 1) * nProfile);
	m->vIndexes.reserve(nSamples * (nProfile - 1) * 6);

	// 2. Generar vértices por revolución
	for (GLuint i = 0; i <= nSamples; ++i) {
		GLfloat ang = angleMax * GLfloat(i) / GLfloat(nSamples);
		GLfloat c = cos(ang);
		GLfloat s = sin(ang);

		for (const auto& p : profile) {
			m->vVertices.emplace_back(p.x * c, p.y, p.x * s);
		}
	}

	// 3. Generar índices para conectar los vértices
	for (GLuint i = 0; i < nSamples; ++i) {
		GLuint curr = i * nProfile;
		GLuint next = (i + 1) * nProfile;

		for (GLuint j = 0; j + 1 < nProfile; ++j) {
			GLuint a = curr + j;
			GLuint b = next + j;
			GLuint c = next + j + 1;
			GLuint d = curr + j + 1;

			// Triángulo 1
			m->vIndexes.push_back(a);
			m->vIndexes.push_back(b);
			m->vIndexes.push_back(c);

			// Triángulo 2
			m->vIndexes.push_back(a);
			m->vIndexes.push_back(c);
			m->vIndexes.push_back(d);
		}
	}

	// 4. PREPARACIÓN FINAL (Orden crítico)
	m->mNumVertices = GLuint(m->vVertices.size());

	// Primero calculamos las normales en la CPU (Apartado 58)
	m->buildNormalVectors();



	return m;
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