#include "GlassCap.h"
#include "Cone.h"
#include "Disk.h"

#include <glm/gtc/matrix_transform.hpp>

GlassCap::GlassCap(GLdouble height, GLdouble rBottom, GLdouble rTop, int lightId)
{
	const glm::vec4 metalA(0.10f, 0.13f, 0.18f, 1.0f);
	const glm::vec4 metalB(0.16f, 0.20f, 0.26f, 1.0f);
	const glm::vec4 cyan(0.20f, 0.85f, 1.00f, 1.0f);

	// Cuerpo principal cónico invertido
	Cone* mainCone = new Cone(height, rBottom, rTop, 3, 48);
	mainCone->setColor(metalA);
	mainCone->setModelMat(glm::mat4(1.0f));
	addEntity(mainCone);

	// Anillo inferior de unión
	Disk* lowerRing = new Disk(rBottom, 0.0, 1, 48);
	lowerRing->setColor(metalB);
	lowerRing->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -height * 0.50f + 6.0f, 0.0f)));
	addEntity(lowerRing);

	// Nivel intermedio
	Disk* midRing = new Disk(rTop * 1.06, rTop * 0.94, 1, 48);
	midRing->setColor(metalB);
	midRing->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -height * 0.08f, 0.0f)));
	addEntity(midRing);

	// Franja luminosa cyan
	Disk* glowRing = new Disk(rTop * 1.03, rTop * 0.97, 1, 48);
	glowRing->setColor(cyan);
	glowRing->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, height * 0.20f, 0.0f)));
	addEntity(glowRing);

	// Tapa superior tecnológica
	Disk* topPlate = new Disk(rTop, 0.0, 1, 48);
	topPlate->setColor(metalA);
	topPlate->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, height * 0.50f, 0.0f)));
	addEntity(topPlate);

	Disk* lampDisk = new Disk(50.0, 20.0, 1, 48);
	lampDisk->setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	lampDisk->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, -height * 0.50f, 0.0f)));
	addEntity(lampDisk);

	mLight = new SpotLight(glm::vec3(0.0f, 0.0f, 0.0f), lightId);
	mLight->setAmb(glm::vec3(0.08f, 0.00f, 0.00f));
	mLight->setDiff(glm::vec3(3.0f, 0.05f, 0.05f));
	mLight->setSpec(glm::vec3(4.0f, 0.10f, 0.10f));
	mLight->setPosition(glm::vec3(0.0f, height * 0.10f, 0.0f));
	mLight->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
	mLight->setCutoff(35.0f, 50.0f);
	mLight->setEnabled(true);
}