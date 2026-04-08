#include "Entity.h"
class RGBRectangle : public EntityWithColors {
public:
	RGBRectangle(GLdouble w, GLdouble h);
	virtual ~RGBRectangle() = default;

	virtual void render(glm::mat4 const& modelViewMat) const override;

	//virtual void load() override;
	//virtual void unload() override;
};
