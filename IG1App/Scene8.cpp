

//#include "Scene8.h"
//#include "Droid.h"
//#include "DathomirPlanet.h"
//#include <glm/gtc/matrix_transform.hpp>
//
//void Scene8::init()
//{
//	glEnable(GL_DEPTH_TEST);
//
//	const GLdouble planetRadius = 150.0;
//	const GLdouble droidRadius = planetRadius * 0.10; // más pequeño que el planeta
//
//	DathomirPlanet* dathomir = new DathomirPlanet(planetRadius, 50, 50);
//	dathomir->setModelMat(glm::mat4(1.0f));
//	gObjects.push_back(dathomir);
//
//	Droid* droid = new Droid(droidRadius);
//	droid->setModelMat(
//		glm::translate(glm::mat4(1.0f),
//			glm::vec3(0.0f, planetRadius + droidRadius, 0.0f)));
//	gObjects.push_back(droid);
//}

#include "Scene8.h"
#include "Droid.h"
#include "DathomirPlanet.h"
#include "CompoundEntity.h"

#include <glm/gtc/matrix_transform.hpp>

void Scene8::init()
{
	Scene::init();
	glEnable(GL_DEPTH_TEST);

	mPlanetRadius = 150.0;
	mDroidRadius = mPlanetRadius * 0.10;
	mRotateAngle = 0.0;
	mOrbitAngle = 0.0;

	DathomirPlanet* dathomir = new DathomirPlanet(mPlanetRadius, 50, 50);
	dathomir->setModelMat(glm::mat4(1.0f));
	gObjects.push_back(dathomir);

	mOrbitNode = new CompoundEntity();
	mOrbitNode->setModelMat(glm::mat4(1.0f));
	gObjects.push_back(mOrbitNode);

	mDroid = new Droid(mDroidRadius);
	updateRotate();
	updateOrbit();
	mOrbitNode->addEntity(mDroid);
}

void Scene8::updateRotate()
{
	if (mDroid == nullptr)
		return;

	mDroid->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, mPlanetRadius + mDroidRadius, 0.0f)) *
		glm::rotate(glm::mat4(1.0f),
			GLfloat(mRotateAngle),
			glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Scene8::updateOrbit()
{
	if (mOrbitNode == nullptr)
		return;

	mOrbitNode->setModelMat(
		glm::rotate(glm::mat4(1.0f),
			GLfloat(mOrbitAngle),
			glm::vec3(1.0f, 0.0f, 0.0f)));
}

void Scene8::rotate()
{
	mRotateAngle += glm::radians(8.0);
	updateRotate();
}

void Scene8::orbit()
{
	mOrbitAngle += glm::radians(10.0);
	updateOrbit();
}