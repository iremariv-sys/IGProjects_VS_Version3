#include "LaboratoryRoom.h"
#include "Ground.h"
#include "BoxOutline.h"
#include <glm/ext/matrix_transform.hpp>

LaboratoryRoom::LaboratoryRoom(GLdouble width, GLdouble depth, GLdouble height,
	Texture* floorTex,
	Texture* wallTexExterior,
	Texture* wallTexInterior)
{
	buildRoom(width, depth, height, floorTex, wallTexExterior, wallTexInterior);
}

LaboratoryRoom::~LaboratoryRoom()
{
	for (Abs_Entity* part : mParts)
		delete part;

	mParts.clear();
}
void LaboratoryRoom::buildRoom(GLdouble width, GLdouble depth, GLdouble height,
	Texture* floorTex,
	Texture* wallTexExterior,
	Texture* wallTexInterior)
{
	const GLdouble thick = 10.0;

	// Suelo
	Abs_Entity* floor = new Ground(width, depth, floorTex);
	floor->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
	mParts.push_back(floor);

	// Pared norte
	Abs_Entity* wallN = new BoxOutline(wallTexExterior, wallTexInterior, width);
	wallN->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, float(height * 0.5), float(-depth * 0.5))) *
		glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, float(height / width), float(thick / width)))
	);
	mParts.push_back(wallN);

	// Pared sur
	Abs_Entity* wallS = new BoxOutline(wallTexExterior, wallTexInterior, width);
	wallS->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, float(height * 0.5), float(depth * 0.5))) *
		glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, float(height / width), float(thick / width)))
	);
	mParts.push_back(wallS);

	// Pared este
	Abs_Entity* wallE = new BoxOutline(wallTexExterior, wallTexInterior, depth);
	wallE->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(float(width * 0.5), float(height * 0.5), 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, float(height / depth), float(thick / depth)))
	);
	mParts.push_back(wallE);

	// Pared oeste
	Abs_Entity* wallW = new BoxOutline(wallTexExterior, wallTexInterior, depth);
	wallW->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(float(-width * 0.5), float(height * 0.5), 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, float(height / depth), float(thick / depth)))
	);
	mParts.push_back(wallW);
}
void LaboratoryRoom::load()
{
	for (Abs_Entity* part : mParts)
		part->load();
}

void LaboratoryRoom::unload()
{
	for (Abs_Entity* part : mParts)
		part->unload();
}

void LaboratoryRoom::update()
{
	for (Abs_Entity* part : mParts)
		part->update();
}

void LaboratoryRoom::render(const glm::mat4& modelViewMat) const
{
	for (Abs_Entity* part : mParts)
		part->render(modelViewMat);
}