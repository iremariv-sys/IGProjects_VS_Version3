#ifndef _H_Box_H_
#define _H_Box_H_

#include "EntityWithTexture.h"
#include "Mesh.h"
#include "Texture.h"
#include <glm/glm.hpp>

// Se usa junto a BoxOutline (las 4 paredes) en la escena.
class Box : public EntityWithTexture
{
public:
    explicit Box(Texture* texExterior, Texture* texInterior, GLdouble length);
    ~Box() override;

    void render(glm::mat4 const& modelViewMat) const override;
    void update() override;
    virtual void load();
    virtual void unload();
private:
    Texture*  mInnerTexture = nullptr;
    Mesh*     mTop          = nullptr; // tapa animada
    Mesh*     mBottom       = nullptr; // fondo estático
    GLdouble  mHalf         = 0.0;

    // Animación de la tapa
    GLdouble  mLidAngle     = 0.0;  // grados: 0=cerrada, 180=abierta
    GLdouble  mLidSpeed     = 1.0;  // grados por llamada a update()
    bool      mLidOpening   = true; // true=abriendo, false=cerrando
};

#endif //_H_Box_H_