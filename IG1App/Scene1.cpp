#include "Scene1.h"
#include "RegularPolygon.h"


void Scene1::init() {
    Scene::init(); 

    gObjects.push_back(
        new RegularPolygon(6, 210.0, glm::vec4(1, 0, 1, 1))
    );

    gObjects.push_back(
        new RegularPolygon(100, 210.0, glm::vec4(1.0, 1.0, 0.0, 1.0))
    );
}