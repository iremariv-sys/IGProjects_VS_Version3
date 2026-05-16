#include "Scene0.h"
#include "LaboratoryRoom.h"
#include "Texture.h"
#include <glm/ext/matrix_transform.hpp>

static Texture* createTexture(const char* path, int repeat)
{
	Texture* tex = new Texture();
	tex->load(path, repeat);
	return tex;
}

void Scene0::init()
{
	Scene::init();
	Texture* floorTex = createTexture("../assets/images/floor.jpg", 1);
	Texture* wallTex = createTexture("../assets/images/lab.jpg", 1);
	Texture* wallTex2 = createTexture("../assets/images/lab.jpg", 1);

	LaboratoryRoom* room = new LaboratoryRoom(4000.0, 4000.0, 1500.0,
		floorTex, wallTex, wallTex2);
	gObjects.push_back(room);

}