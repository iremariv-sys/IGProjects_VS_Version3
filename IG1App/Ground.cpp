#include "Ground.h"
#include "Mesh.h"

#include <glm/gtc/matrix_transform.hpp>


Ground::Ground(GLdouble w, GLdouble h, Texture* tex)
    : EntityWithTexture(tex, false)
{
  
    mMesh = Mesh::generaRectangleTexCor(w, h, 4, 4); // Apartado 21
    // Rotamos el suelo para que quede horizontal
    glm::mat4 model = glm::rotate(
        glm::mat4(1.0f),
        glm::radians(-90.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    setModelMat(model);
}
