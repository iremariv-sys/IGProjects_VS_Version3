//#ifndef _H_Scene8_H_
//#define _H_Scene8_H_
//
//#include "Scene.h"
//
//class Scene8 : public Scene
//{
//public:
//	void init() override;
//};
//
//#endif //_H_Scene8_H_
#ifndef _H_Scene8_H_
#define _H_Scene8_H_

#include "Scene.h"

class CompoundEntity;
class Droid;

class Scene8 : public Scene
{
public:
	void init() override;
	void rotate() override;
	void orbit() override;

private:
	void updateRotate();
	void updateOrbit();

	CompoundEntity* mOrbitNode = nullptr;
	Droid* mDroid = nullptr;

	GLdouble mPlanetRadius = 0.0;
	GLdouble mDroidRadius = 0.0;
	GLdouble mRotateAngle = 0.0;
	GLdouble mOrbitAngle = 0.0;
};

#endif //_H_Scene8_H_