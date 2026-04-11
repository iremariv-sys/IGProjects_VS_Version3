//#include "ColorMaterialEntity.h"

//using namespace glm;

//ColorMaterialEntity::ColorMaterialEntity(glm::vec4 color)
//	: SingleColorEntity(color)
	
//{
//	mShader = Shader::get("simple_light");
//}

///void ColorMaterialEntity::render(mat4 const& modelViewMat) const
//{
//	if (mMesh != nullptr && mShader != nullptr) {
//		mat4 aMat = modelViewMat * mModelMat;
//		mShader->use();
	
//		upload(aMat);
//		mMesh->render();
//	}
//}

#include "ColorMaterialEntity.h"

using namespace glm;

ColorMaterialEntity::ColorMaterialEntity(glm::vec4 color)
	: SingleColorEntity(color)
{
	mShader = Shader::get("simple_light");
}

void ColorMaterialEntity::render(mat4 const& modelViewMat) const
{
	if (mMesh != nullptr && mShader != nullptr) {
		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("color", mColor);
		upload(aMat);
		mMesh->render();
	}
}