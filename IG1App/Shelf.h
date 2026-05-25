

#ifndef _H_Shelf_H_
#define _H_Shelf_H_

#include "CompoundEntity.h"
#include "Light.h"

class Shelf : public CompoundEntity
{
public:
	explicit Shelf(int lightId = -1);

	SpotLight* light() const { return mLight; }

private:
	SpotLight* mLight = nullptr;
};

#endif //_H_Shelf_H_