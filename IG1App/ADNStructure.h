//
//#include "CompoundEntity.h"
//
//class ADNStructure : public CompoundEntity
//{
//public:
//    ADNStructure();
//    void update() override;
//
//private:
//    float mRotationY = 0.0f;
//    float mSpeed = 5.0f;
//};

#ifndef _H_ADNStructure_H_
#define _H_ADNStructure_H_

#include "CompoundEntity.h"
#include <glm/glm.hpp>

class ADNStructure : public CompoundEntity
{
public:
    ADNStructure();
    void update() override;

    void setBaseMat(const glm::mat4& mat) { mBaseMat = mat; }

private:
    glm::mat4 mBaseMat = glm::mat4(1.0f);
    float mRotationY = 0.0f;
    float mSpeed = 3.0f;
};

#endif //_H_ADNStructure_H_