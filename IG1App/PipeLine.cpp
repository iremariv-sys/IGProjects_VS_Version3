#include "Pipeline.h"
#include "IndexedBox.h"

#include <glm/gtc/matrix_transform.hpp>

Pipeline::Pipeline()
{
	const glm::vec4 pipeDark(0.18f, 0.20f, 0.24f, 1.0f);
	const glm::vec4 pipeMetal(0.28f, 0.30f, 0.34f, 1.0f);

	IndexedBox* pipe1 = new IndexedBox(1.0);
	pipe1->setColor(pipeMetal);
	pipe1->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 18.0f, -950.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(70.0f, 14.0f, 1700.0f)));
	addEntity(pipe1);

	IndexedBox* pipe2 = new IndexedBox(1.0);
	pipe2->setColor(pipeMetal);
	pipe2->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 18.0f, 950.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(70.0f, 14.0f, 1700.0f)));
	addEntity(pipe2);

	IndexedBox* pipe3 = new IndexedBox(1.0);
	pipe3->setColor(pipeDark);
	pipe3->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(-950.0f, 18.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(1700.0f, 14.0f, 70.0f)));
	addEntity(pipe3);

	IndexedBox* pipe4 = new IndexedBox(1.0);
	pipe4->setColor(pipeDark);
	pipe4->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(950.0f, 18.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(1700.0f, 14.0f, 70.0f)));
	addEntity(pipe4);

	mGlowNorth = new IndexedBox(1.0);
	mGlowNorth->setColor(glm::vec4(0.20f, 0.90f, 1.0f, 1.0f));
	mGlowNorth->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 27.0f, -950.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(18.0f, 3.0f, 1500.0f)));
	addEntity(mGlowNorth);

	mGlowSouth = new IndexedBox(1.0);
	mGlowSouth->setColor(glm::vec4(0.30f, 1.0f, 0.55f, 1.0f));
	mGlowSouth->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 27.0f, 950.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(18.0f, 3.0f, 1500.0f)));
	addEntity(mGlowSouth);

	mGlowWest = new IndexedBox(1.0);
	mGlowWest->setColor(glm::vec4(0.15f, 0.45f, 1.0f, 1.0f));
	mGlowWest->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(-950.0f, 27.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(1500.0f, 3.0f, 18.0f)));
	addEntity(mGlowWest);

	mGlowEast = new IndexedBox(1.0);
	mGlowEast->setColor(glm::vec4(1.0f, 0.25f, 0.25f, 1.0f));
	mGlowEast->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(950.0f, 27.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(1500.0f, 3.0f, 18.0f)));
	addEntity(mGlowEast);
}

glm::vec4 Pipeline::colorForPhase(int phase) const
{
	switch (phase % 4) {
	case 0:
		return glm::vec4(0.20f, 0.90f, 1.0f, 1.0f);
	case 1:
		return glm::vec4(0.30f, 1.0f, 0.55f, 1.0f);
	case 2:
		return glm::vec4(0.15f, 0.45f, 1.0f, 1.0f);
	default:
		return glm::vec4(1.0f, 0.25f, 0.25f, 1.0f);
	}
}

void Pipeline::update()
{
	CompoundEntity::update();

	mBlinkCounter += 1;

	int phase = (mBlinkCounter / 16) % 4;

	if (mGlowNorth != nullptr)
		mGlowNorth->setColor(colorForPhase(phase));

	if (mGlowSouth != nullptr)
		mGlowSouth->setColor(colorForPhase(phase + 1));

	if (mGlowWest != nullptr)
		mGlowWest->setColor(colorForPhase(phase + 2));

	if (mGlowEast != nullptr)
		mGlowEast->setColor(colorForPhase(phase + 3));
}