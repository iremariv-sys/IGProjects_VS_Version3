#include "Droid.h"
#include "Cone.h"
#include "SphereWithTexture.h"

#include <glm/gtc/matrix_transform.hpp>

namespace
{
    class GreenCylinder : public Cone
    {
    public:
        GreenCylinder(GLdouble h, GLdouble r, GLuint nRings, GLuint nSamples)
            : Cone(h, r, r, nRings, nSamples)
        {
            mColor = glm::vec4(0.0f, 0.8f, 0.0f, 1.0f);
        }
    };
}

Droid::Droid(GLdouble radius)
{
    SphereWithTexture* head = new SphereWithTexture(radius, 20, 32);
    head->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, radius * 1.35)));
    addEntity(head);

    Cone* body = new Cone(radius, radius / 2.0, radius / 2.0, 20, 32);
    body->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -radius * 0.15)));
    addEntity(body);

    GreenCylinder* leftLeg = new GreenCylinder(radius * 1.5, radius * 0.18, 16, 24);
    leftLeg->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(-radius * 0.65, 0.0f, -radius * 1.25)));
    addEntity(leftLeg);

    GreenCylinder* rightLeg = new GreenCylinder(radius * 1.5, radius * 0.18, 16, 24);
    rightLeg->setModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(radius * 0.65, 0.0f, -radius * 1.25)));
    addEntity(rightLeg);
}
