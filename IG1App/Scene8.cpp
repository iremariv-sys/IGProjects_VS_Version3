


#include "Scene8.h"
#include "Droid.h"
#include "DathomirPlanet.h"
#include "CompoundEntity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

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

	// Apartado 77

	mPosLight = new PosLight(0);
	mPosLight->setAmb(glm::vec3(0.25f, 0.25f, 0.25f));
	mPosLight->setDiff(glm::vec3(0.6f, 0.6f, 0.6f));
	mPosLight->setSpec(glm::vec3(0.0f, 0.2f, 0.0f));
	mPosLight->setPosition(glm::vec3(0.0f, mPlanetRadius * 2.0f, 0.0f));
	mPosLight->setEnabled(true);
	gLights.push_back(mPosLight);

	// Foco apartado 78
	mSpotLight = new SpotLight(glm::vec3(0.0f, mPlanetRadius * 2.0f, mPlanetRadius * 2.0f), 0);
	mSpotLight->setAmb(glm::vec3(0.25f, 0.25f, 0.25f));
	mSpotLight->setDiff(glm::vec3(0.6f, 0.6f, 0.6f));
	mSpotLight->setSpec(glm::vec3(0.0f, 0.2f, 0.0f));
	mSpotLight->setPosition(glm::vec3(0.0f, 0.0f, 300.0f));
	mSpotLight->setDirection(glm::vec3(0.0f, 0.0f, -1.0f));
	mSpotLight->setCutoff(5.0f, 8.0f);// tamaño del foco
	mSpotLight->setEnabled(false);
	gLights.push_back(mSpotLight);

	mOrbitNode = new CompoundEntity();
	mOrbitNode->setModelMat(glm::mat4(1.0f));
	gObjects.push_back(mOrbitNode);

	mHeadingNode = new CompoundEntity();
	mHeadingNode->setModelMat(glm::mat4(1.0f));
	mOrbitNode->addEntity(mHeadingNode);

	mDroid = new Droid(mDroidRadius);
	mDroid->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, mPlanetRadius + mDroidRadius, 0.0f)));
	mHeadingNode->addEntity(mDroid);

	

	
	mBellyLight = new SpotLight(glm::vec3(0.0f, 0.0f, 0.0f), 1);
	mBellyLight->setAmb(glm::vec3(0.0f, 0.0f, 0.0f));
	mBellyLight->setDiff(glm::vec3(1.0f, 0.9f, 0.9f));
	mBellyLight->setSpec(glm::vec3(1.0f, 0.9f, 0.9f));
	mBellyLight->setCutoff(55.0f, 70.0f);
	mBellyLight->setAttenuation(1.0f, 0.0015f, 0.00005f);
	mBellyLight->setEnabled(false);
	gLights.push_back(mBellyLight);
	updateRotate();
	updateBellyLight();

}

void Scene8::updateRotate()
{
	if (mHeadingNode == nullptr)
		return;

	mHeadingNode->setModelMat(
		glm::rotate(glm::mat4(1.0f),
			GLfloat(mRotateAngle),
			glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Scene8::updateOrbit()
{
}

void Scene8::rotate()
{
	mRotateAngle += glm::radians(8.0);
	updateRotate();
	//Apartado 79
	updateBellyLight();
}

void Scene8::orbit()
{
	if (mOrbitNode == nullptr)
		return;

	GLfloat step = glm::radians(10.0f);

	glm::vec3 axisLocal(
		cos(GLfloat(mRotateAngle)),
		0.0f,
		-sin(GLfloat(mRotateAngle)));

	mOrbitNode->setModelMat(
		mOrbitNode->modelMat() *
		glm::rotate(glm::mat4(1.0f), step, axisLocal));
	updateBellyLight();
}
glm::vec4 Scene8::clearColor() const
{
	return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}


//Apartado 77
void Scene8::togglePosLight()
{
	if (mPosLight != nullptr)
		mPosLight->setEnabled(!mPosLight->enabled());
}

//Apartado 78
void Scene8::toggleSpotLight()
{
	if (mSpotLight != nullptr)
		mSpotLight->setEnabled(!mSpotLight->enabled());
}

//Apartado 79

//void Scene8::updateBellyLight()
//{
//	if (mBellyLight == nullptr || mOrbitNode == nullptr || mHeadingNode == nullptr || mDroid == nullptr)
//		return;
//
//	glm::mat4 worldMat =
//		mOrbitNode->modelMat() *
//		mHeadingNode->modelMat() *
//		mDroid->modelMat();
//
//	// Centrado debajo del droide
//	glm::vec4 localPos(0.0f, -mDroidRadius * 0.5f, 0.0f, 1.0f);
//	glm::vec4 worldPos = worldMat * localPos;
//
//	// Hacia abajo, ligeramente abierto hacia delante
//	glm::vec3 localDir = glm::normalize(glm::vec3(0.0f, -1.0f, 0.15f));
//	glm::vec3 worldDir = glm::normalize(glm::mat3(worldMat) * localDir);
//
//	mBellyLight->setPosition(glm::vec3(worldPos));
//	mBellyLight->setDirection(worldDir);
//}

void Scene8::updateBellyLight()
{
	if (mBellyLight == nullptr || mOrbitNode == nullptr || mHeadingNode == nullptr || mDroid == nullptr)
		return;

	glm::mat4 worldMat =
		mOrbitNode->modelMat() *
		mHeadingNode->modelMat() *
		mDroid->modelMat();

	glm::vec4 localPos(0.0f, -mDroidRadius * 0.35f, 0.0f, 1.0f);
	glm::vec3 localDir(0.0f, -1.0f, 0.0f);

	glm::vec4 worldPos = worldMat * localPos;
	glm::vec3 worldDir = glm::normalize(glm::mat3(worldMat) * localDir);

	mBellyLight->setPosition(glm::vec3(worldPos));
	mBellyLight->setDirection(worldDir);
}

void Scene8::toggleBellyLight()
{
	if (mBellyLight != nullptr)
		mBellyLight->setEnabled(!mBellyLight->enabled());
}