#include "ColorMaterialEntity.h"

class Disk : public ColorMaterialEntity
{
public:
	Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples);
};