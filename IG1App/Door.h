
#ifndef _H_Door_H_
#define _H_Door_H_

#include "CompoundEntity.h"

class Texture;

class Door : public CompoundEntity
{
public:
	Door(Texture* doorTex);
};

#endif //_H_Door_H_