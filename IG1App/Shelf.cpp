
#include "Shelf.h"
#include "IndexedBox.h"

#include <glm/gtc/matrix_transform.hpp>

Shelf::Shelf(int lightId)
{


	const glm::vec4 frameColor(0.12f, 0.14f, 0.18f, 1.0f);
	const glm::vec4 shelfColor(0.22f, 0.26f, 0.32f, 1.0f);
	const glm::vec4 boxColor(0.18f, 0.20f, 0.24f, 1.0f);
	const glm::vec4 accentColor(1.0f, 0.20f, 0.20f, 1.0f);

	IndexedBox* leftFrame = new IndexedBox(1.0);
	leftFrame->setColor(frameColor);
	leftFrame->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(-220.0f, 260.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 520.0f, 20.0f)));
	addEntity(leftFrame);

	IndexedBox* rightFrame = new IndexedBox(1.0);
	rightFrame->setColor(frameColor);
	rightFrame->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(220.0f, 260.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 520.0f, 20.0f)));
	addEntity(rightFrame);

	IndexedBox* shelf1 = new IndexedBox(1.0);
	shelf1->setColor(shelfColor);
	shelf1->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 130.0f, 20.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(460.0f, 18.0f, 70.0f)));
	addEntity(shelf1);

	IndexedBox* shelf2 = new IndexedBox(1.0);
	shelf2->setColor(shelfColor);
	shelf2->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 250.0f, 20.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(460.0f, 18.0f, 70.0f)));
	addEntity(shelf2);

	IndexedBox* shelf3 = new IndexedBox(1.0);
	shelf3->setColor(shelfColor);
	shelf3->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 370.0f, 20.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(460.0f, 18.0f, 70.0f)));
	addEntity(shelf3);

	IndexedBox* box1 = new IndexedBox(1.0);
	box1->setColor(boxColor);
	box1->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(-110.0f, 165.0f, 35.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(60.0f, 60.0f, 50.0f)));
	addEntity(box1);

	IndexedBox* box2 = new IndexedBox(1.0);
	box2->setColor(boxColor);
	box2->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(90.0f, 285.0f, 35.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(80.0f, 50.0f, 45.0f)));
	addEntity(box2);

	IndexedBox* box3 = new IndexedBox(1.0);
	box3->setColor(boxColor);
	box3->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(-40.0f, 425.0f, 35.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(70.0f, 70.0f, 50.0f)));
	addEntity(box3);

	IndexedBox* backPanel = new IndexedBox(1.0);
	backPanel->setColor(shelfColor);
	backPanel->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 260.0f, -5.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(460.0f, 520.0f, 6.0f)));
	addEntity(backPanel);

	IndexedBox* glow = new IndexedBox(1.0);
	glow->setColor(accentColor);
	glow->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 485.0f, 35.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(220.0f, 8.0f, 8.0f)));
	addEntity(glow);


	if (lightId >= 0) {
		mLight = new SpotLight(glm::vec3(0.0f, 0.0f, 0.0f), lightId);
		mLight->setAmb(glm::vec3(0.05f, 0.03f, 0.03f));
		mLight->setDiff(glm::vec3(1.50f, 0.55f, 0.50f));
		mLight->setSpec(glm::vec3(1.00f, 0.38f, 0.34f));
		mLight->setAttenuation(1.0f, 0.0015f, 0.00005f);
		mLight->setPosition(glm::vec3(0.0f, 470.0f, 35.0f));
		mLight->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
		mLight->setCutoff(40.0f, 60.0f);
		mLight->setEnabled(true);
	}
}