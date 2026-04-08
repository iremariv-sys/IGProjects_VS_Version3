#include "Entity.h"
#include "Texture.h"
#include "EntityWithTexture.h"


class Ground : public EntityWithTexture
{
public:
    Ground(GLdouble w, GLdouble h, Texture* tex);
};

