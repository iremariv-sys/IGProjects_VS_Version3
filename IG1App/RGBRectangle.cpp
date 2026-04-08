#include "RGBRectangle.h"

RGBRectangle::RGBRectangle(GLdouble w, GLdouble h) : EntityWithColors() {
    mMesh = Mesh::generateRGBRectangle(w, h);
}

void RGBRectangle::render(glm::mat4 const& modelViewMat) const
{
    if (mMesh == nullptr || mShader == nullptr) return;

    glm::mat4 aMat = modelViewMat * mModelMat;
    mShader->use();
    upload(aMat);

    GLboolean wasCull = glIsEnabled(GL_CULL_FACE);
    glEnable(GL_CULL_FACE);

    // BACK relleno
    glCullFace(GL_FRONT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    mMesh->render();

    // FRONT líneas
    glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    mMesh->render();

    // restaurar
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (!wasCull) glDisable(GL_CULL_FACE);
}

