

#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Light.h"
#include <vector>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene();

	Scene(const Scene& s) = delete;
	Scene& operator=(const Scene& s) = delete;

	virtual void init();
	virtual void update();

	virtual void rotate();
	virtual void orbit();
	virtual void savePhoto();
	virtual void render(Camera const& cam) const;
	virtual glm::vec4 clearColor() const;

	void load();
	void unload();

	//Apartado 76
	void toggleDirLight();
	//apartado 77
	virtual void togglePosLight();
	//Apartado 78
	virtual void toggleSpotLight();
	//Apartado 79
	virtual void toggleBellyLight();
protected:
	void destroy();
	void setGL();
	void resetGL();
	void uploadLights(const glm::mat4& viewMat) const;

	std::vector<Abs_Entity*> gObjects;
	std::vector<Light*> gLights;
};

#endif //_H_Scene_H_