#ifndef _H_LightColumn_H_
#define _H_LightColumn_H_

#include "CompoundEntity.h"
#include "IndexedBox.h"
#include "Light.h"

class LightColumn : public CompoundEntity
{
public:
	LightColumn(GLdouble height, GLdouble thickness, const glm::vec4& glowColor, const glm::vec3& worldPos, int lightId);

	PosLight* light() const { return mLight; }

private:
	PosLight* mLight = nullptr;
};

#endif //_H_LightColumn_H_