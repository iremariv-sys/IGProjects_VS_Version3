#include "ColorMaterialEntity.h"

class HexagonalBase : public ColorMaterialEntity
{
public:
    HexagonalBase();
    void render(const glm::mat4& modelViewMat) const override;

private:
    glm::mat4 mLower;
    glm::mat4 mMiddle;
    glm::mat4 mUpper;
};