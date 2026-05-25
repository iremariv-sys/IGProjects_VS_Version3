

#include "SingleColorEntity.h"

class CircularGlass : public SingleColorEntity
{
public:
    CircularGlass(GLdouble radius, GLdouble height, glm::vec4 color);
    void render(glm::mat4 const& modelViewMat) const override;
};