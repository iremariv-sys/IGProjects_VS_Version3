
#include "ColorMaterialEntity.h"


using namespace glm;

bool ColorMaterialEntity::mShowNormals = false;

ColorMaterialEntity::ColorMaterialEntity(glm::vec4 color)
	: EntityWithMaterial()
{
	setColor(color);
}

void ColorMaterialEntity::setColor(const glm::vec4& color)
{
	glm::vec3 rgb(color.r, color.g, color.b);
	mMaterial.setAmb(rgb);
	mMaterial.setDiff(rgb);
	mMaterial.setSpec(rgb);
	mMaterial.setExp(8.0f);
}

void ColorMaterialEntity::toggleShowNormals()
{
	mShowNormals = !mShowNormals;
}

void ColorMaterialEntity::render(mat4 const& modelViewMat) const
{
	EntityWithMaterial::render(modelViewMat);

	if (mShowNormals) {
		Shader* normalsShader = Shader::get("normals");
		if (normalsShader != nullptr) {
			mat4 aMat = modelViewMat * mModelMat;
			glDepthMask(GL_FALSE);
			normalsShader->use();
			normalsShader->setUniform("modelView", aMat);
			mMesh->render();
			glDepthMask(GL_TRUE);
		}
	}
}