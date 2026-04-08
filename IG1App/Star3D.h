#include "EntityWithTexture.h"
#include "Mesh.h"


class Star3D : public EntityWithTexture {
public:
   
    //Star3D(GLdouble re, GLuint np, GLdouble h, glm::dvec4 const& color);
    Star3D(GLdouble re, GLuint np, GLdouble h, Texture* tex);
    void update() override;
    
   
    void render(glm::mat4 const& modelViewMat) const override;

    //void syncModelMats() { mLowerModelMat = mModelMat; }
    void setPosition(glm::vec3 const& pos);
    void setModelMat(glm::mat4 const& aMat);

private:
    GLdouble mRe;   // radio exterior
    GLuint   mNp;   // número de puntas
    GLdouble mH;    // altura (z = +h y z = -h)
    glm::vec3 mPos;
    glm::mat4 mLowerModelMat= glm::mat4(1.0f);
};