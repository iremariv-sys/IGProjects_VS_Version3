
#include "Torus.h"
#include "IndexMesh.h"

#include <cmath>
#include <glm/gtc/constants.hpp>

using namespace glm;

Torus::Torus(GLdouble R, GLdouble r, GLuint nPoints, GLuint nSamples)
	: ColorMaterialEntity(vec4(0.0f, 1.0f, 0.0f, 1.0f))
{
	std::vector<glm::vec2> profile;
	profile.reserve(nPoints);

	for (GLuint i = 0; i < nPoints; ++i) {
		GLdouble a = glm::two_pi<GLdouble>() * GLdouble(i) / GLdouble(nPoints);
		GLdouble x = R + r * cos(a);
		GLdouble y = r * sin(a);
		profile.emplace_back(GLfloat(x), GLfloat(y));
	}

	mMesh = IndexMesh::generateByRevolution(
		profile,
		nSamples,
		glm::two_pi<GLdouble>(),
		true);
}

///dinamiccast