#include "HexagonalBase.h"
#include "IndexMesh.h"

#include <glm/gtc/matrix_transform.hpp>

HexagonalBase::HexagonalBase()
    : ColorMaterialEntity(glm::vec4(0.22f, 0.24f, 0.28f, 1.0f))
{
    mMesh = IndexMesh::generateHexagonalPrism(1.0, 1.0);

    material().setAmb(glm::vec3(0.08f, 0.09f, 0.10f));
    material().setDiff(glm::vec3(0.22f, 0.24f, 0.28f));
    material().setSpec(glm::vec3(0.90f, 0.95f, 1.00f));
    material().setExp(48.0f);

    mLower = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 20.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(250.0f, 40.0f, 250.0f));

    mMiddle = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 55.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(180.0f, 30.0f, 180.0f));

    mUpper = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 80.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(120.0f, 20.0f, 120.0f));
}

void HexagonalBase::render(const glm::mat4& modelViewMat) const
{
    if (mMesh == nullptr || mShader == nullptr)
        return;

    glm::mat4 aMat = modelViewMat * mModelMat;

    mShader->use();
    mMaterial.upload(*mShader);

    upload(aMat * mLower);
    mMesh->render();

    upload(aMat * mMiddle);
    mMesh->render();

    upload(aMat * mUpper);
    mMesh->render();
}