
#include "Door.h"
#include "IndexedBox.h"
#include "EntityWithTexture.h"
#include "Mesh.h"
#include "Texture.h"

#include <glm/gtc/matrix_transform.hpp>

class DoorPanel : public EntityWithTexture
{
public:
	explicit DoorPanel(Texture* tex)
		: EntityWithTexture(tex)
	{
		mMesh = Mesh::generaRectangleTexCor(1.0, 1.0, 1, 1);
	}
};

Door::Door(Texture* doorTex)
{
	const glm::vec4 frameColor(0.12f, 0.14f, 0.18f, 1.0f);
	const glm::vec4 handleColor(0.28f, 0.30f, 0.34f, 1.0f);

	IndexedBox* frame = new IndexedBox(1.0);
	frame->setColor(frameColor);
	frame->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 260.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(50.0f, 550.0f, 520.0f)));
	addEntity(frame);

	DoorPanel* leaf = new DoorPanel(doorTex);
	leaf->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(29.0f, 250.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(510.0f, -150.0f, 720.0f)));
	addEntity(leaf);
	IndexedBox* handle = new IndexedBox(1.0);
	handle->setColor(handleColor);
	handle->setModelMat(
		glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 250.0f, 70.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 30.0f, 8.0f)));
	addEntity(handle);
}