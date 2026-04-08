#include "GlassParapet.h"


GlassParapet::GlassParapet(GLdouble length, Texture* tex)
    : EntityWithTexture(tex)
{
    mMesh = Mesh::generateBoxOutlineTexCor(length);
}

void GlassParapet::render(glm::mat4 const& modelViewMat) const
{
    if (mMesh == nullptr || mShader == nullptr) return;

    glm::mat4 aMat = modelViewMat * mModelMat;
    mShader->use();
    mShader->setUniform("modulate", mModulate);
    upload(aMat);

    // Activar mezcla para transparencia
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    
    glDepthMask(GL_FALSE);

    // Caras exteriores
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    if (mTexture != nullptr) mTexture->bind();
    mMesh->render();

    // Caras interiores (textura traslúcida)
    glCullFace(GL_FRONT);
    mMesh->render();

    if (mTexture != nullptr) mTexture->unbind();

    glDisable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}