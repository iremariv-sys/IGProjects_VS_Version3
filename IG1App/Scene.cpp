#include "Scene.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"
#include "Ground.h"
#include <iostream>

using namespace glm;

void
Scene::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Texture
	gObjects.push_back(new RGBAxes(400.0));


	DirLight* dirLight = new DirLight(0);
	dirLight->setAmb(glm::vec3(0.25f, 0.25f, 0.25f));
	dirLight->setDiff(glm::vec3(0.6f, 0.6f, 0.6f));
	dirLight->setSpec(glm::vec3(0.0f, 0.2f, 0.0f));
	dirLight->setDirection(glm::vec3(-1.0f, -1.5f, -1.25f));
	dirLight->setEnabled(true);
	gLights.push_back(dirLight);
}

Scene::~Scene()
{
	destroy();
	resetGL();
}

void
Scene::destroy()
{ // release memory and resources

	for (Abs_Entity* el : gObjects)
		delete el;

	gObjects.clear();

	for (Light* light : gLights)
		delete light;
	gLights.clear();

}

void
Scene::load()
{
	for (Abs_Entity* obj : gObjects)
		obj->load();

	//Apartado 76
	//for (Light* light : gLights)
	//	light->setEnabled(true);
	
}

void
Scene::unload()
{
	for (Abs_Entity* obj : gObjects)
		obj->unload();
	//Apartado 76
	for (Light* light : gLights)
		light->setEnabled(false);
}

void
Scene::setGL()
{
	// OpenGL basic setting
	//glClearColor(1.0, 1.0, 1.0, 1.0); // background color (alpha=1 -> opaque)
	glClearColor(0.6f, 0.7f, 0.8f, 1.0f);
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
}

//void
//Scene::render(Camera const& cam) const
//{
//	cam.upload();
//	for (Abs_Entity* el : gObjects) {
//		el->render(cam.viewMat());
//	
//	}
//
//}
void Scene::render(Camera const& cam) const
{
	cam.upload();
	uploadLights(cam.viewMat());

	for (Abs_Entity* el : gObjects)
		el->render(cam.viewMat());
}


void Scene::uploadLights(const glm::mat4& viewMat) const
{
	Shader* lightShader = Shader::get("light");
	if (lightShader == nullptr)
		return;

	lightShader->use();

	const int NR_DIR_LIGHTS = 2;
	const int NR_POS_LIGHTS = 4;
	const int NR_SPOT_LIGHTS = 4;

	for (int i = 0; i < NR_DIR_LIGHTS; ++i)
		lightShader->setUniform("dirLights[" + std::to_string(i) + "].enabled", false);

	for (int i = 0; i < NR_POS_LIGHTS; ++i)
		lightShader->setUniform("posLights[" + std::to_string(i) + "].enabled", false);

	for (int i = 0; i < NR_SPOT_LIGHTS; ++i)
		lightShader->setUniform("spotLights[" + std::to_string(i) + "].enabled", false);

	for (Light* light : gLights)
		light->upload(*lightShader, viewMat);
}

void Scene::update() {
	for (Abs_Entity* obj : gObjects)
		obj->update();
}

//Apartado 76

void Scene::toggleDirLight()
{
	if (!gLights.empty())
		gLights[0]->setEnabled(!gLights[0]->enabled());
}

//Apartado 77
void Scene::togglePosLight()
{
}

//Apartado 78
void Scene::toggleSpotLight()
{
}
//Apartado 79
void Scene::toggleBellyLight()
{
}
void Scene::rotate()
{
}

void Scene::orbit()
{
}

glm::vec4 Scene::clearColor() const
{
	return glm::vec4(0.6f, 0.7f, 0.8f, 1.0f);
}
void Scene::savePhoto() {}