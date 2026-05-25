#include "LightColumn.h"

#include <glm/gtc/matrix_transform.hpp>

LightColumn::LightColumn(GLdouble height, GLdouble thickness, const glm::vec4& glowColor, const glm::vec3& worldPos, int lightId)
{
	setModelMat(glm::translate(glm::mat4(1.0f), worldPos));

	const glm::vec4 metal(0.18f, 0.20f, 0.24f, 1.0f);

	IndexedBox* base = new IndexedBox(1.0);
	base->setColor(metal);
	base->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 20.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(thickness * 1.25f, 40.0f, thickness * 1.25f)));
	addEntity(base);

	IndexedBox* body = new IndexedBox(1.0);
	body->setColor(glowColor);
	body->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 20.0f + height * 0.5f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(thickness, height, thickness)));
	addEntity(body);

	IndexedBox* top = new IndexedBox(1.0);
	top->setColor(glowColor);
	top->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 20.0f + height + 20.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(thickness * 1.15f, 30.0f, thickness * 1.15f)));
	addEntity(top);

	mLight = new PosLight(lightId);
	mLight->setAmb(glm::vec3(0.02f, 0.02f, 0.02f));
	mLight->setDiff(glm::vec3(0.12f, 0.26f, 0.20f));
	mLight->setSpec(glm::vec3(0.08f, 0.18f, 0.14f));
	mLight->setAttenuation(1.0f, 0.010f, 0.0008f);
	mLight->setPosition(worldPos + glm::vec3(0.0f, height + 60.0f, 0.0f));
	mLight->setEnabled(true);
}