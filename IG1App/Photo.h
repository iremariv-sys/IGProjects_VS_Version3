#ifndef _H_Photo_H_
#define _H_Photo_H_

#include "EntityWithTexture.h"
#include "Mesh.h"
#include "Texture.h"

class Photo : public EntityWithTexture {
public:
    Photo(GLsizei winW, GLsizei winH, GLdouble w, GLdouble h);
    ~Photo();

    // Capturamos el back-buffer justo en el render, y luego dibujamos
    void render(glm::mat4 const& modelViewMat) const override;
    void capture();
    void saveToBMP(const char* filename) const;
private:
    GLsizei mWinW;
    GLsizei mWinH;
};

#endif //_H_Photo_H_



