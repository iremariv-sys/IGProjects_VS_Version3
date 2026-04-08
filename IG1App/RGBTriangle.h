#include "Entity.h"

//APARTADO 7 -- DECLARAMOS LA CLASE EntityWithColor
class RGBTriangle : public EntityWithColors {
public:
	RGBTriangle(GLdouble r);
	virtual ~RGBTriangle() = default;
	//virtual void render(glm::mat4 const& modelViewMat) const override;
	virtual void update() ; //apartado 12
};

