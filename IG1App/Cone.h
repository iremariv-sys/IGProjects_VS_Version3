#include "ColorMaterialEntity.h"

class Cone : public ColorMaterialEntity
{
public:
	Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples);
};