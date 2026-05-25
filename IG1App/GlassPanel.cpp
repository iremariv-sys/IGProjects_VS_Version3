#include "GlassPanel.h"
#include "IndexMesh.h"
#include <glm/gtc/matrix_transform.hpp>

CircularGlass::CircularGlass(GLdouble radius, GLdouble height, glm::vec4 color)
    : SingleColorEntity(color)
{
    std::vector<glm::vec2> profile;
    profile.push_back(glm::vec2(radius, 0.0f));
    profile.push_back(glm::vec2(radius, static_cast<float>(height)));

    mMesh = IndexMesh::generateByRevolution(profile, 32);
}

void CircularGlass::render(glm::mat4 const& modelViewMat) const
{
    if (mMesh == nullptr || mShader == nullptr)
        return;

    glm::mat4 aMat = modelViewMat * mModelMat;

    mShader->use();
    mShader->setUniform("color", mColor);
    upload(aMat);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    mMesh->render();

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}