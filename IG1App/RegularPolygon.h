#include "SingleColorEntity.h"
#include "Mesh.h"

class RegularPolygon : public SingleColorEntity {
public:
	RegularPolygon(GLuint num, GLdouble r, const glm :: vec4& color = glm::vec4(1.0));
};
