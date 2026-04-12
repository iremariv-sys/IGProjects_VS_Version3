#include "Cone.h"
#include "IndexMesh.h"

#include <vector>

Cone::Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples)
	: ColorMaterialEntity(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f))
{
	std::vector<glm::vec2> profile;

	for (GLuint i = 0; i <= nRings; ++i) {
		GLdouble t = (nRings == 0) ? 0.0 : GLdouble(i) / GLdouble(nRings);
		GLdouble radius = r + (R - r) * t;
		GLdouble y = -h / 2.0 + h * t;

		profile.push_back(glm::vec2(radius, y));
	}

	mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}