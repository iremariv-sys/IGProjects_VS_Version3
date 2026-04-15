#include "Droid.h"
#include "Cone.h"
#include "Disk.h"
#include "SphereWithTexture.h"
#include "EntityWithTexture.h"
#include "IndexMesh.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

namespace
{
	std::vector<glm::vec2> buildConeProfile(GLdouble h, GLdouble r, GLdouble R, GLuint nRings)
	{
		std::vector<glm::vec2> profile;
		profile.reserve(nRings + 1);

		for (GLuint i = 0; i <= nRings; ++i) {
			GLdouble t = (nRings == 0) ? 0.0 : GLdouble(i) / GLdouble(nRings);
			GLdouble radius = r + (R - r) * t;
			GLdouble y = -h / 2.0 + h * t;
			profile.push_back(glm::vec2(radius, y));
		}

		return profile;
	}

	std::vector<glm::vec2> buildDiskProfile(GLdouble R, GLdouble r, GLuint nRings)
	{
		std::vector<glm::vec2> profile;
		profile.reserve(nRings + 1);

		for (GLuint i = 0; i <= nRings; ++i) {
			GLdouble t = (nRings == 0) ? 0.0 : GLdouble(i) / GLdouble(nRings);
			GLdouble radius = r + (R - r) * t;
			profile.push_back(glm::vec2(radius, 0.0));
		}

		return profile;
	}

	class TexturedRevolution : public EntityWithTexture
	{
	public:
		TexturedRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples, const char* texturePath)
			: EntityWithTexture(new Texture(), false)
		{
			mTexture->load(texturePath);
			setMesh(IndexMesh::generateByRevolution(profile, nSamples));
		}

		virtual ~TexturedRevolution() override
		{
			delete mTexture;
			mTexture = nullptr;
		}
	};

	class GreenCone : public Cone
	{
	public:
		GreenCone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples)
			: Cone(h, r, R, nRings, nSamples)
		{
			mColor = glm::vec4(0.0f, 0.8f, 0.0f, 1.0f);
		}
	};

	class Hat : public CompoundEntity
	{
	public:
		explicit Hat(GLdouble radius)
		{
			const char* hatTexture = "../assets/images/noche.jpg";

			TexturedRevolution* lowerCone = new TexturedRevolution(
				buildConeProfile(radius * 0.30, radius * 0.95, radius * 0.70, 8),
				12,
				hatTexture);
			lowerCone->setModelMat(glm::mat4(1.0f));
			addEntity(lowerCone);

			TexturedRevolution* lid = new TexturedRevolution(
				buildDiskProfile(radius * 0.72, 0.0, 1),
				12,
				hatTexture);
			lid->setModelMat(
				glm::translate(glm::mat4(1.0f),
					glm::vec3(0.0f, radius * 0.150f, 0.0f)));
			addEntity(lid);

			GLdouble yArm = radius * 0.10f;

			GreenCone* arm1 = new GreenCone(
				radius * 0.35, radius * 0.06, radius * 0.06, 12, 24);
			arm1->setModelMat(
				glm::translate(glm::mat4(1.0f),
					glm::vec3(-radius * 0.75f, yArm, -radius * 0.25f)) *
				glm::rotate(glm::mat4(1.0f),
					glm::half_pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f)));
			addEntity(arm1);

			GreenCone* arm2 = new GreenCone(
				radius * 0.35, radius * 0.06, radius * 0.06, 12, 24);
			arm2->setModelMat(
				glm::translate(glm::mat4(1.0f),
					glm::vec3(-radius * 0.75f, yArm, radius * 0.25f)) *
				glm::rotate(glm::mat4(1.0f),
					glm::half_pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f)));
			addEntity(arm2);
		}
	};
}

Droid::Droid(GLdouble radius)
{
	SphereWithTexture* body = new SphereWithTexture(radius, 20, 32);
	body->setModelMat(glm::mat4(1.0f));
	addEntity(body);

	Hat* hat = new Hat(radius);
	hat->setModelMat(
		glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, radius * 1.125f, 0.0f)));
	addEntity(hat);
}