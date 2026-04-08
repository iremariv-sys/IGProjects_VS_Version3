
#include "Star3D.h"
#include <glm/gtc/matrix_transform.hpp> 
#include "Mesh.h"
#include "Texture.h"


Star3D::Star3D(GLdouble re, GLuint np, GLdouble h, Texture* tex)
    : EntityWithTexture(tex)
    , mRe(re)
    , mNp(np)
    , mH(h)
    , mPos(0.0f, 200.0f, 0.0f)
    , mLowerModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 200.0f, 0.0f)))
{
    mMesh = Mesh::generateStar3DTexCor(re, np, h);
}

void Star3D::render(glm::mat4 const& modelViewMat) const
{
    if (mMesh == nullptr || mShader == nullptr) return;

    mShader->use();
    mShader->setUniform("modulate", mModulate);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (mTexture != nullptr) mTexture->bind();

    // Estrella superior
    glm::mat4 upperMV = modelViewMat * mModelMat;
    upload(upperMV);
    mMesh->render();

    // Estrella inferior (reflejada en Z)
    glm::mat4 mirrorMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, -1.0f));
    glm::mat4 lowerMV = modelViewMat * mLowerModelMat * mirrorMat;
    upload(lowerMV);
    mMesh->render();

    if (mTexture != nullptr) mTexture->unbind();
}

void Star3D::update()
{
    static float angZ = 0.0f;
    static float angZLower = 0.0f;

    angZ += 2.0f;
    angZLower -= 2.0f;

    mModelMat = glm::translate(glm::mat4(1.0f), mPos);
    mModelMat = glm::rotate(mModelMat, glm::radians(angZ), glm::vec3(0.0f, 0.0f, 1.0f));

    mLowerModelMat = glm::translate(glm::mat4(1.0f), mPos);
    mLowerModelMat = glm::rotate(mLowerModelMat, glm::radians(angZLower), glm::vec3(0.0f, 0.0f, 1.0f));
}
void Star3D::setPosition(glm::vec3 const& pos)
{
    mPos = pos;
    
    glm::mat4 t = glm::translate(glm::mat4(1.0f), mPos);
    Abs_Entity::setModelMat(t); // actualiza mModelMat base
    mLowerModelMat = t;
}

void Star3D::setModelMat(glm::mat4 const& aMat)
{
    
    Abs_Entity::setModelMat(aMat);
    mLowerModelMat = aMat;

    glm::vec4 col = aMat[3];
    mPos = glm::vec3(col.x, col.y, col.z);
}