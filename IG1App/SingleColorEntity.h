#include "Entity.h"
// APARTADO 3 ------------------------------------------------------------------
class SingleColorEntity : public Abs_Entity {
public:
	SingleColorEntity(glm::vec4 color);
	virtual ~SingleColorEntity() = default;
	virtual void render(glm::mat4 const& modelViewMat) const override;
	virtual void update(float deltaTime) {}
	//add
	void setColor(const glm::vec4& color) { mColor = color; }
protected:
	glm::vec4 mColor;
};