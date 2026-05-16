#include "EntityWithMaterial.h"

using namespace glm;

bool EntityWithMaterial::mShowNormals = false;

EntityWithMaterial::EntityWithMaterial()
{
	//mShader = Shader::get("simple_light");
	mShader = Shader::get("light");
}

void
EntityWithMaterial::toggleShowNormals()
{
	mShowNormals = !mShowNormals;
}

void
EntityWithMaterial::render(mat4 const& modelViewMat) const
{
	if (mMesh == nullptr || mShader == nullptr)
		return;

	mat4 aMat = modelViewMat * mModelMat;

	mShader->use();
	mMaterial.upload(*mShader);
	upload(aMat);
	mMesh->render();

	if (mShowNormals) {
		Shader* normalsShader = Shader::get("normals");
		if (normalsShader != nullptr) {
			glDepthMask(GL_FALSE);
			normalsShader->use();
			normalsShader->setUniform("modelView", aMat);
			mMesh->render();
			glDepthMask(GL_TRUE);
		}
	}
}