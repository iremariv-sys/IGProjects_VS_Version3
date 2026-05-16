#pragma once

#include "Entity.h"
#include <vector>

class Texture;

class LaboratoryRoom : public Abs_Entity
{
public:
	explicit LaboratoryRoom(GLdouble width, GLdouble depth, GLdouble height,
		Texture* floorTex,
		Texture* wallTexExterior,
		Texture* wallTexInterior);

	~LaboratoryRoom() override;

	void load() override;
	void unload() override;
	void update() override;
	void render(const glm::mat4& modelViewMat) const override;

private:
	void buildRoom(GLdouble width, GLdouble depth, GLdouble height,
		Texture* floorTex,
		Texture* wallTexExterior,
		Texture* wallTexInterior);

	std::vector<Abs_Entity*> mParts;
};