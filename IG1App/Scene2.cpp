#include "Scene2.h"
#include "RGBTriangle.h"
#include "RGBRectangle.h"
#include "RegularPolygon.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

void Scene2:: init() {

	Scene::init();

	
	RGBTriangle* tri = new RGBTriangle(40.0);

	tri->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 0.0f, 0.0f)));
	
	gObjects.push_back(tri);

	gObjects.push_back(
		new RGBRectangle(282.84f, 282.84f));

	gObjects.push_back(
		new RegularPolygon(60, 200.0, glm::vec4(1, 0, 1, 1)));
};

void Scene2::update() {
	for (Abs_Entity* obj : gObjects) {
		if (RGBTriangle* tri = dynamic_cast<RGBTriangle*>(obj)) {
			tri->update();
		}
	}
}