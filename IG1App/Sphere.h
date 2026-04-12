
#ifndef _H_Sphere_H_
#define _H_Sphere_H_

#include "ColorMaterialEntity.h"

class Sphere : public ColorMaterialEntity
{
public:
	Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians);
};

#endif //_H_Sphere_H_
