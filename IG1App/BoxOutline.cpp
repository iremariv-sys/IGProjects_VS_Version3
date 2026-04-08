#include "BoxOutline.h"
#include "Entity.h"
#include "Shader.h"

BoxOutline::BoxOutline(Texture* texExterior, Texture* texInterior, GLdouble length)
    : EntityWithTexture(texExterior), mInnerTexture(texInterior)
{
    mMesh = Mesh::generateBoxOutlineTexCor(length);
}

void BoxOutline::render(glm::mat4 const& modelViewMat) const
{
    if (mMesh == nullptr || mShader == nullptr) return;

    glm::mat4 aMat = modelViewMat * mModelMat;
    mShader->use();
    mShader->setUniform("modulate", mModulate);
    upload(aMat);

    glEnable(GL_CULL_FACE);

    // Exterior: solo caras frontales
    glCullFace(GL_BACK);
    if (mTexture != nullptr) mTexture->bind();
    mMesh->render();
    if (mTexture != nullptr) mTexture->unbind();

    // Interior: solo caras traseras
    glCullFace(GL_FRONT);
    if (mInnerTexture != nullptr) mInnerTexture->bind();
    mMesh->render();
    if (mInnerTexture != nullptr) mInnerTexture->unbind();

    glDisable(GL_CULL_FACE);
}