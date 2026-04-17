#include "SingleColorEntity.h"
using namespace glm;

//APARTADO 4 ESCENA 1
// Constructor
SingleColorEntity::SingleColorEntity(glm::vec4 color)
    : Abs_Entity()
{

    mColor = color;
    mShader = Shader::get("simple");
}

void
SingleColorEntity::render(mat4 const& modelViewMat) const
{
	
	
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("color", mColor);
		upload(aMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	
}
