#include "EntityWithTexture.h"

class Grass : public EntityWithTexture
{
public:
    Grass(GLdouble width, GLdouble height, Texture* tex);
    void render(glm::mat4 const& modelViewMat) const override;
private:
    GLdouble mHalf = 0.0; // altura/2 para centrar la base en y=0
};
