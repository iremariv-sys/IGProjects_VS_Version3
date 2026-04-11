
#include "ColorMaterialEntity.h"

class Torus : public  ColorMaterialEntity //SingleColorEntity
{
public:
	Torus(GLdouble R, GLdouble r, GLuint nPoints = 40, GLuint nSamples = 40);
};