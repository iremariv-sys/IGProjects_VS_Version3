#include "SnowMan.h"

#include "Sphere.h"
#include "Cone.h"
#include "Disk.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>


	const glm::vec4 LIGHT_GRAY(243.0f / 255.0f, 243.0f / 255.0f, 243.0f / 255.0f, 1.0f);
	const glm::vec4 ORANGE(1.0f, 0.5f, 0.0f, 1.0f);
	const glm::vec4 TEAL(0.0f, 128.0f / 255.0f, 128.0f / 255.0f, 1.0f);
	const glm::vec4 BLUE(0.0f, 0.0f, 1.0f, 1.0f);
	const glm::vec4 RED(1.0f, 0.0f, 0.0f, 1.0f);
	const glm::vec4 CYAN(0.0f, 1.0f, 1.0f, 1.0f);

SnowMan::SnowMan(GLdouble radius)
{
	// Cuerpo inferior
	Sphere* lowerBody = new Sphere(radius, 16, 24);
	lowerBody->setColor(LIGHT_GRAY);
	lowerBody->setModelMat(glm::mat4(1.0f));
	addEntity(lowerBody);

	// Cuerpo superior
	GLdouble upperRadius = radius * 0.65;
	Sphere* upperBody = new Sphere(upperRadius, 16, 24);
	upperBody->setColor(LIGHT_GRAY);
	upperBody->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, radius + upperRadius, 0.0f)));
	addEntity(upperBody);

	// Nariz: cono naranja mirando a +Z
	Cone* nose = new Cone(radius * 0.18, radius * 0.08, 0.0, 8, 12);
	nose->setColor(ORANGE);
	nose->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, radius + upperRadius * 0.20f, upperRadius * 0.75f)) *
		glm::rotate(glm::mat4(1.0f),
			glm::half_pi<float>(),
			glm::vec3(1.0f, 0.0f, 0.0f)));
	addEntity(nose);

	// Ojos: dos conos color (0,128,128)
	Cone* eye1 = new Cone(radius * 0.12, radius * 0.08, 0.0, 8, 12);
	eye1->setColor(TEAL);
	eye1->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(-radius * 0.18f, radius + upperRadius * 0.62f, upperRadius * 0.82f)) *
		glm::rotate(glm::mat4(1.0f),
			glm::half_pi<float>(),
			glm::vec3(1.0f, 0.0f, 0.0f)));
	addEntity(eye1);

	Cone* eye2 = new Cone(radius * 0.12, radius * 0.08, 0.0, 8, 12);
	eye2->setColor(TEAL);
	eye2->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(radius * 0.18f, radius + upperRadius * 0.62f, upperRadius * 0.82f)) *
		glm::rotate(glm::mat4(1.0f),
			glm::half_pi<float>(),
			glm::vec3(1.0f, 0.0f, 0.0f)));
	addEntity(eye2);

	// Sombrero: cilindro azul + discos rojo y cyan
	GLdouble hatRadius = radius * 0.35;
	GLdouble hatHeight = radius * 0.60;
	GLdouble hatCenterY = radius + upperRadius + radius * 0.55f;

	Cone* hatCylinder = new Cone(hatHeight, hatRadius, hatRadius, 8, 12);
	hatCylinder->setColor(BLUE);
	hatCylinder->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, hatCenterY, 0.0f)));
	addEntity(hatCylinder);

	Disk* redDisk = new Disk(hatRadius, 0.0, 1, 12);
	redDisk->setColor(RED);
	redDisk->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, hatCenterY + hatHeight * 0.5f, 0.0f)));
	addEntity(redDisk);

	Disk* cyanDisk = new Disk(hatRadius, 0.0, 1, 12);
	cyanDisk->setColor(CYAN);
	cyanDisk->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, hatCenterY - hatHeight * 0.5f, 0.0f)));
	addEntity(cyanDisk);
}