#include "Scene8.h"
#include "Droid.h"
#include "DathomirPlanet.h"
#include <glm/gtc/matrix_transform.hpp>

void Scene8::init()
{
	// Establecer fondo negro solo para esta escena
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Planeta Dathomir: esfera granate (171, 33, 72)
	DathomirPlanet* dathomir = new DathomirPlanet(120.0, 40, 40);
	dathomir->setModelMat(glm::mat4(1.0f));
	gObjects.push_back(dathomir);

	// Droid en el polo norte
	Droid* droid = new Droid(40.0);
	droid->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 120.0f + 40.0f, 0.0f)));
	gObjects.push_back(droid);
}
