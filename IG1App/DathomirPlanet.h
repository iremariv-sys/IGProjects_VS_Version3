#ifndef _H_DathomirPlanet_H_
#define _H_DathomirPlanet_H_

#include "ColorMaterialEntity.h"

class DathomirPlanet : public ColorMaterialEntity
{
public:
	DathomirPlanet(GLdouble radius, GLuint nParallels, GLuint nMeridians);
};

#endif //_H_DathomirPlanet_H_
