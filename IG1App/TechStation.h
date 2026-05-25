#ifndef _H_TechStation_H_
#define _H_TechStation_H_

#include "CompoundEntity.h"
#include "IndexedBox.h"
#include "EntityWithTexture.h"
#include "Texture.h"

class TechStation : public CompoundEntity
{
public:
    TechStation(Texture* screenTex);

private:
    Texture* mScreenTex = nullptr;
};

#endif //_H_TechStation_H_