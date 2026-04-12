#include "Sphere.h"
#include "IndexMesh.h"

#include <vector>
#include <glm/gtc/constants.hpp>

Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians)
	: ColorMaterialEntity(glm::vec4(1.0f, 0.6f, 0.2f, 1.0f))
{
	std::vector<glm::vec2> profile;

	for (GLuint i = 0; i <= nParallels; ++i) {
		GLdouble t = GLdouble(i) / GLdouble(nParallels);
		GLdouble ang = -glm::half_pi<GLdouble>() + t * glm::pi<GLdouble>();

		GLdouble r = radius * cos(ang);
		GLdouble y = radius * sin(ang);

		profile.push_back(glm::vec2(r, y));
	}

	//mMesh = IndexMesh::generateByRevolution(profile, nMeridians);
	mMesh = IndexMesh::generateSphere(radius, nParallels, nMeridians);
}