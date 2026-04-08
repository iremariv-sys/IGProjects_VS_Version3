#include "Box.h"
#include "Shader.h"
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>

Box::Box(Texture* texExterior, Texture* texInterior, GLdouble length)
    : EntityWithTexture(texExterior)
    , mInnerTexture(texInterior)
    , mHalf(length / 2.0)
{
    // Solo tapa y fondo. Las 4 paredes las gestiona BoxOutline en la escena.
    mTop    = Mesh::generaRectangleTexCor(length, length, 1, 1);
    mBottom = Mesh::generaRectangleTexCor(length, length, 1, 1);
}

Box::~Box()
{
    delete mTop;
    mTop = nullptr;
    delete mBottom;
    mBottom = nullptr;
}

void Box::load()
{
    if (mTop    != nullptr) mTop->load();
    if (mBottom != nullptr) mBottom->load();
}

void Box::unload()
{
    if (mTop    != nullptr) mTop->unload();
    if (mBottom != nullptr) mBottom->unload();
}

void Box::update()
{
    // La tapa se abre hasta 180° y vuelve a cerrarse
    if (mLidOpening) {
        mLidAngle += mLidSpeed;
        if (mLidAngle >= 180.0) {
            mLidAngle   = 180.0;
            mLidOpening = false;
        }
    }
    else {
        mLidAngle -= mLidSpeed;
        if (mLidAngle <= 0.0) {
            mLidAngle   = 0.0;
            mLidOpening = true;
        }
    }
}

void Box::render(glm::mat4 const& modelViewMat) const
{
    if (mShader == nullptr) return;

    glm::mat4 aMat = modelViewMat * mModelMat;
    mShader->use();
    mShader->setUniform("modulate", mModulate);

    // --- Tapa animada (bisagra en borde posterior z = -mHalf) ---
    if (mTop != nullptr) {
        glm::mat4 Mt = glm::translate(aMat, glm::vec3(0.0f, float(mHalf), 0.0f));
        Mt = glm::translate(Mt, glm::vec3(0.0f, 0.0f, float(-mHalf)));
        //moviemiento del la caja 
        Mt = glm::rotate(Mt, glm::radians(float(-mLidAngle)), glm::vec3(1.0f, 0.0f, 0.0f));
        Mt = glm::translate(Mt, glm::vec3(0.0f, 0.0f, float(mHalf)));
        upload(Mt);

        glEnable(GL_CULL_FACE);

        glCullFace(GL_BACK);
        if (mTexture      != nullptr) mTexture->bind();
        mTop->render();
        if (mTexture      != nullptr) mTexture->unbind();

        glCullFace(GL_FRONT);
        if (mInnerTexture != nullptr) mInnerTexture->bind();
        mTop->render();
        if (mInnerTexture != nullptr) mInnerTexture->unbind();

        glDisable(GL_CULL_FACE);
    }

    // --- Fondo estático (y = -mHalf) ---
    if (mBottom != nullptr) {
        glm::mat4 Mb = glm::translate(aMat, glm::vec3(0.0f, float(-mHalf), 0.0f));
        Mb = glm::rotate(Mb, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        upload(Mb);

        glEnable(GL_CULL_FACE);

        glCullFace(GL_BACK);
        if (mTexture      != nullptr) mTexture->bind();
        mBottom->render();
        if (mTexture      != nullptr) mTexture->unbind();

        glCullFace(GL_FRONT);
        if (mInnerTexture != nullptr) mInnerTexture->bind();
        mBottom->render();
        if (mInnerTexture != nullptr) mInnerTexture->unbind();

        glDisable(GL_CULL_FACE);
    }
}