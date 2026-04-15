#include "DathomirPlanet.h"
#include "IndexMesh.h"

DathomirPlanet::DathomirPlanet(GLdouble radius, GLuint nParallels, GLuint nMeridians)
	: ColorMaterialEntity(glm::vec4(171.0f / 255.0f, 33.0f / 255.0f, 72.0f / 255.0f, 1.0f))
{
	mMesh = IndexMesh::generateSphere(radius, nParallels, nMeridians);
}
