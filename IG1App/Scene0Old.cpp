#include "Scene0Old.h"
#include "Sphere.h"

#include <glm/gtc/matrix_transform.hpp>


void Scene0Old::init()
{
	Scene::init();

	Sphere* goldPlanet = new Sphere(70.0, 40, 40);
	Material gold;
	gold.setGold();
	goldPlanet->setMaterial(gold);
	goldPlanet->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(50.0f, 0.0f, 180.0f)));
	gObjects.push_back(goldPlanet);

	Sphere* yellowPlanet = new Sphere(70.0, 40, 40);
	yellowPlanet->setColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	yellowPlanet->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(180.0f, 0.0f, 10.0f)));
	gObjects.push_back(yellowPlanet);
}