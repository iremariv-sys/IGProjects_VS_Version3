
#ifndef _H_SphereWithTexture_H_
#define _H_SphereWithTexture_H_

#include "EntityWithTexture.h"

class SphereWithTexture : public EntityWithTexture
{
public:
    SphereWithTexture(GLdouble radius, GLuint nParallel, GLuint nMeridians);
    virtual ~SphereWithTexture() override;
};

#endif //_H_SphereWithTexture_H_
