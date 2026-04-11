#include "Scene5.h"
#include "Torus.h"

void Scene5::init()
{
	Scene::init();

	Torus* torus = new Torus(120.0, 55.0, 12, 40);
	gObjects.push_back(torus);
}