#ifndef _H_Scene0_H_
#define _H_Scene0_H_

#include "Scene.h"
#include <array>
#include <vector>

class Texture;
class Pipeline;
class Shelf;
class MechanicalArm;
class IndexedBox;
class ADNStructure;
class EntityWithTexture;

class Scene0 : public Scene
{
public:
	~Scene0() override;

	void init() override;
	void update() override;
	void togglePosLight() override;
	void toggleSpotLight() override;
	glm::vec4 clearColor() const override;
	void addShelf(const glm::vec3& pos, float angleDeg, int lightId, SpotLight*& outLight);


private:
	Texture* createTexture(const char* path, int repeat);
	IndexedBox* createBox(const glm::vec3& pos);
	EntityWithTexture* createPanel(Texture* tex, const glm::vec3& pos, float angleDeg);

	

	// cleanup helper
	//void clearTextures();
	

	SpotLight* mSpotLight = nullptr;
	Pipeline* mPipeline = nullptr;

	PosLight* mColumnLight1 = nullptr;
	PosLight* mColumnLight2 = nullptr;
	PosLight* mColumnLight3 = nullptr;
	PosLight* mColumnLight4 = nullptr;
	
	SpotLight* mShelfLight1 = nullptr;
	SpotLight* mShelfLight2 = nullptr;
	SpotLight* mShelfLight3 = nullptr;

	bool mColumnsEnabled = true;

	std::vector<Texture*> mTextures;

	MechanicalArm* mArm = nullptr;
	IndexedBox* mBox = nullptr;

	MechanicalArm* mArm2 = nullptr;
	IndexedBox* mBox2 = nullptr;

	float mAnimTime = 0.0f;

};

#endif //_H_Scene0_H_