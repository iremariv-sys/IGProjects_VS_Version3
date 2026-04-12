#pragma once

#include <vector>

#include "Entity.h"

class CompoundEntity : public Abs_Entity
{
public:
    CompoundEntity() = default;
    virtual ~CompoundEntity() override;

    void addEntity(Abs_Entity* ae);

    virtual void render(glm::mat4 const& modelViewMat) const override;
    virtual void update() override;
    virtual void load() override;
    virtual void unload() override;

protected:
    std::vector<Abs_Entity*> gObjects;
};

