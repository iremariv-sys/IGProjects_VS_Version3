#include "EntityWithTexture.h"
#include "Texture.h"
#include "Shader.h"
EntityWithTexture::EntityWithTexture(Texture* tex, bool modulate) : Abs_Entity()
{
    mTexture = tex;
    mModulate = modulate;
    mShader = Shader::get("texture");
}

void EntityWithTexture::render(glm::mat4 const& modelViewMat) const
{
    if (mMesh == nullptr || mShader == nullptr)
        return;

    glm::mat4 aMat = modelViewMat * mModelMat;

    mShader->use();
    mShader->setUniform("modulate", mModulate);
    upload(aMat);

    if (mTexture != nullptr)
    {
        
        mTexture->bind();
      
        mMesh->render();
        mTexture->unbind();
    }
    else
        mMesh->render();
}



