#include "CompoundEntity.h"

using namespace glm;

CompoundEntity::~CompoundEntity()
{
    for (Abs_Entity* entity : gObjects)
        delete entity;

    gObjects.clear();
}

void CompoundEntity::addEntity(Abs_Entity* ae)
{
    if (ae != nullptr)
        gObjects.push_back(ae);
}

void CompoundEntity::render(mat4 const& modelViewMat) const
{
    mat4 aMat = modelViewMat * mModelMat;

    for (Abs_Entity* entity : gObjects)
        entity->render(aMat);
}

void CompoundEntity::update()
{
    for (Abs_Entity* entity : gObjects)
        entity->update();
}

void CompoundEntity::load()
{
    for (Abs_Entity* entity : gObjects)
        entity->load();
}

void CompoundEntity::unload()
{
    for (Abs_Entity* entity : gObjects)
        entity->unload();
}
