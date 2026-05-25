#ifndef GLASSCAP_H
#define GLASSCAP_H

#include "CompoundEntity.h"
#include "Light.h"

class GlassCap : public CompoundEntity
{
public:
	GlassCap(GLdouble height, GLdouble rBottom, GLdouble rTop, int lightId);
	SpotLight* light() const { return mLight; }

private:
	SpotLight* mLight = nullptr;
};

#endif // GLASSCAP_H