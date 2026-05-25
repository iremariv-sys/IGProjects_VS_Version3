#include "Chair.h"
#include "IndexedBox.h"

#include <glm/gtc/matrix_transform.hpp>

Chair::Chair()
{
	const glm::vec4 seatColor(0.20f, 0.16f, 0.12f, 1.0f);
	const glm::vec4 legColor(0.25f, 0.25f, 0.27f, 1.0f);
	const glm::vec4 backColor(0.18f, 0.14f, 0.10f, 1.0f);

	// Asiento
	IndexedBox* seat = new IndexedBox(1.0);
	seat->setColor(seatColor);
	seat->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 70.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 12.0f, 100.0f)));
	addEntity(seat);

	// Respaldo
	IndexedBox* back = new IndexedBox(1.0);
	back->setColor(backColor);
	back->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 120.0f, -35.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(90.0f, 90.0f, 12.0f)));
	addEntity(back);

	// Patas
	IndexedBox* leg1 = new IndexedBox(1.0);
	leg1->setColor(legColor);
	leg1->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(-35.0f, 18.0f, -35.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 100.0f, 10.0f)));
	addEntity(leg1);

	IndexedBox* leg2 = new IndexedBox(1.0);
	leg2->setColor(legColor);
	leg2->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 18.0f, -35.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 100.0f, 10.0f)));
	addEntity(leg2);

	IndexedBox* leg3 = new IndexedBox(1.0);
	leg3->setColor(legColor);
	leg3->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(-35.0f, 18.0f, 35.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 100.0f, 10.0f)));
	addEntity(leg3);

	IndexedBox* leg4 = new IndexedBox(1.0);
	leg4->setColor(legColor);
	leg4->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 18.0f, 35.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 100.0f, 10.0f)));
	addEntity(leg4);
}