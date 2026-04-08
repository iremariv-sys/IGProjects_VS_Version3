#include "Scene3.h"
#include "RGBCube.h"
void Scene3::init() {

	Scene::init();

	gObjects.push_back(
		new RGBCube(200.0));
	

};