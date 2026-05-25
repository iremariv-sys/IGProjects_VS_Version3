
#include "ADNStructure.h"
#include "IndexedBox.h"

#include <glm/gtc/matrix_transform.hpp>

ADNStructure::ADNStructure()
{
    const int levels = 28;
    const float stepY = 18.0f;
    const float radius = 50.0f;
    const float cubeSize = 18.0f;
    const float barLength = 64.0f;
    const float barThickness = 5.0f;
    const float angleStep = glm::radians(22.0f);

    for (int i = 0; i < levels; ++i) {
        float ang = i * angleStep;
        float y = i * stepY;

        float x1 = radius * cos(ang);
        float z1 = radius * sin(ang);

        float x2 = -x1;
        float z2 = -z1;

        IndexedBox* left = new IndexedBox(cubeSize);
        left->setColor(glm::vec4(0.06f, 0.20f, 0.55f, 1.0f));
        left->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(x1, y, z1)));
        addEntity(left);

        IndexedBox* right = new IndexedBox(cubeSize);
        right->setColor(glm::vec4(0.55f, 0.06f, 0.06f, 1.0f));
        right->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(x2, y, z2)));
        addEntity(right);

        glm::vec3 mid(0.0f, y, 0.0f);
        glm::vec3 dir = glm::normalize(glm::vec3(x2 - x1, 0.0f, z2 - z1));
        float barAngle = atan2(dir.z, dir.x);

        IndexedBox* bar = new IndexedBox(1.0);
        bar->setColor(glm::vec4(0.25f, 0.85f, 0.55f, 1.0f));
        bar->setModelMat(
            glm::translate(glm::mat4(1.0f), mid) *
            glm::rotate(glm::mat4(1.0f), barAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(barLength, barThickness, barThickness)));
        addEntity(bar);
    }
}

void ADNStructure::update()
{
    mRotationY += mSpeed;
    if (mRotationY >= 360.0f) {
        mRotationY -= 360.0f;
    }

    mModelMat =
        mBaseMat *
        glm::rotate(glm::mat4(1.0f), glm::radians(mRotationY), glm::vec3(0.0f, 1.0f, 0.0f));
}