//#include "Scene9.h"
//
//void Scene9::init()
//{
//	Scene::init();
//	// aquí añadir objetos de la escena 9
//}


#include "Scene9.h"
#include "SnowMan.h"

void Scene9::init()
{
	//setGL();
	Scene::init();
	SnowMan* snowMan = new SnowMan(60.0);
	snowMan->setModelMat(glm::mat4(1.0f));
	gObjects.push_back(snowMan);
}