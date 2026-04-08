#include "Grass.h"
#include "Mesh.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

Grass::Grass(GLdouble width, GLdouble height, Texture* tex)
    : EntityWithTexture(tex)
    , mHalf(height / 2.0)
{
    mMesh = Mesh::generaRectangleTexCor(width, height, 1, 1);
    mShader = Shader::get("texture");
}

void Grass::render(glm::mat4 const& modelViewMat) const
{
    if (mMesh == nullptr || mShader == nullptr) return;

    mShader->use();
    mShader->setUniform("modulate", mModulate);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    glDisable(GL_CULL_FACE);

    if (mTexture != nullptr)
        mTexture->bind();

    glm::mat4 worldMat = modelViewMat * mModelMat;

    for (int i = 0; i < 6; i++)
    {
        glm::mat4 rotMat = glm::rotate(
            worldMat,
            glm::radians(30.0f * i),
            glm::vec3(0.0f, 1.0f, 0.0f)  
        );
        //  base al suelo (y=0) 
        rotMat = glm::translate(rotMat, glm::vec3(0.0f, float(mHalf), 0.0f));
        rotMat = glm::rotate(rotMat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        upload(rotMat);
        mMesh->render();
    }

    if (mTexture != nullptr)
        mTexture->unbind();

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}