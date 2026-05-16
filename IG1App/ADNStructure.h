
#include "CompoundEntity.h"

class ADNStructure : public CompoundEntity
{
public:
    ADNStructure();
    void update() override;

private:
    float mRotationY = 0.0f;
    float mSpeed = 10.0f;
};