#include "Droid.h"
#include "Cone.h"
#include "Disk.h"
#include "SphereWithTexture.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>



	const glm::vec4 YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
	const glm::vec4 GREEN(0.0f, 0.8f, 0.0f, 1.0f);

	class Head : public CompoundEntity
	{
	public:
		explicit Head(GLdouble radius)
		{
			Cone* cone = new Cone(radius * 0.30, radius * 0.95, radius * 0.5, 8, 12);
			cone->setColor(YELLOW);
			cone->setModelMat(glm::mat4(1.0f));
			addEntity(cone);

			Disk* lid = new Disk(radius * 0.5, 0.0, 1, 12);
			lid->setColor(YELLOW);
			lid->setModelMat(
				glm::translate(glm::mat4(1.0f),
					glm::vec3(0.0f, radius * 0.150f, 0.0f)));
			addEntity(lid);

			GLdouble yEyes = radius * 0.18;
			GLdouble xEyes = radius * 0.14;
			GLdouble zEyes = radius * 0.78;

			Cone* eye1 = new Cone(radius * 0.35, radius * 0.06, radius * 0.06, 12, 24);
			eye1->setColor(GREEN);
			eye1->setModelMat(
				glm::translate(glm::mat4(1.0f),
					glm::vec3(-xEyes, yEyes, zEyes)) *
				glm::rotate(glm::mat4(1.0f),
					glm::half_pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f)));
			addEntity(eye1);

			Cone* eye2 = new Cone(radius * 0.35, radius * 0.06, radius * 0.06, 12, 24);
			eye2->setColor(GREEN);
			eye2->setModelMat(
				glm::translate(glm::mat4(1.0f),
					glm::vec3(xEyes, yEyes, zEyes)) *
				glm::rotate(glm::mat4(1.0f),
					glm::half_pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f)));
			addEntity(eye2);
		}
	};


Droid::Droid(GLdouble radius)
{
	SphereWithTexture* body = new SphereWithTexture(radius, 20, 32);
	body->setModelMat(glm::mat4(1.0f));
	addEntity(body);

	Head* head = new Head(radius);
	head->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, radius * 1.125f, 0.0f)));
	addEntity(head);
}