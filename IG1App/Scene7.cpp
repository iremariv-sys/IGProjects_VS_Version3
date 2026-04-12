#include "Scene7.h"
#include "Droid.h"

void Scene7::init()
{
	Scene::init();

	Droid* robot = new Droid(60.0);
	gObjects.push_back(robot);
}
