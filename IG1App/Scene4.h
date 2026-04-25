#ifndef _H_Scene4_H_
#define _H_Scene4_H_
#include "Scene.h"
#include "Texture.h"
class Photo;
class Scene4 : public Scene
{
public:

	Photo* mPhoto = nullptr;
	void init() override;
	void update() override;
	void savePhoto() override;
	~Scene4();

	//Texture* groundTex;
	//Texture* boxTex;
	//Texture* boxTexInterior;
	//Texture* boxLidTex;
	//Texture* boxLidTexInterior;
	//Texture* starTex;
	//Texture* glassTex;
	//Texture* grassTex;  
	Texture* groundTex = nullptr;  
	Texture* boxTex = nullptr;
	Texture* boxTexInterior = nullptr;
	Texture* boxLidTex = nullptr;
	Texture* boxLidTexInterior = nullptr;
	Texture* starTex = nullptr;
	Texture* glassTex = nullptr;
	Texture* grassTex = nullptr;
	
};

#endif //_H_Scene4_H_

