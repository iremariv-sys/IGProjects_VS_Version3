#include "Disk.h"
#include "IndexMesh.h"

#include <vector>

Disk::Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples)
	: ColorMaterialEntity(glm::vec4(0.2f, 0.8f, 0.2f, 1.0f))
{
	std::vector<glm::vec2> profile;

	for (GLuint i = 0; i <= nRings; ++i) {
		GLdouble t = (nRings == 0) ? 0.0 : GLdouble(i) / GLdouble(nRings);
		GLdouble radius = r + (R - r) * t;

		profile.push_back(glm::vec2(radius, 0.0));
	}

	mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}