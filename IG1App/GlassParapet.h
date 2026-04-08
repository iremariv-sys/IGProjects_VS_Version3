#include "EntityWithTexture.h"
#include "Mesh.h"

class GlassParapet : public EntityWithTexture
{
public:
    GlassParapet(GLdouble length, Texture* tex);
    void render(glm::mat4 const& modelViewMat) const override;
};