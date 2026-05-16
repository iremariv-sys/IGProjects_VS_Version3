#include "Scene0.h"
#include "LaboratoryRoom.h"
#include "Texture.h"
#include <glm/ext/matrix_transform.hpp>
#include "HexagonalBase.h"
#include "ADNStructure.h"

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

	HexagonalBase* base = new HexagonalBase();
	gObjects.push_back(base);

	ADNStructure* adn = new ADNStructure();
	adn->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
	gObjects.push_back(adn);

}