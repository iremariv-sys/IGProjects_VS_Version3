#ifndef _H_EntityWithTexture_H_
#define _H_EntityWithTexture_H_

#include "Entity.h"
#include "Texture.h"

class EntityWithTexture : public Abs_Entity
{
public:
    EntityWithTexture(Texture* tex = nullptr, bool modulate = false);
    virtual ~EntityWithTexture() = default;

    virtual void render(glm::mat4 const& modelViewMat) const override;

    // Método para asignar la malla
    void setMesh(Mesh* mesh) { mMesh = mesh; }

protected:
    //Mesh* mMesh = nullptr;         // puntero a la malla
    Texture* mTexture = nullptr;   // puntero a la textura
    
    //Shader* mShader = nullptr;
    bool mModulate = false;
};

#endif //_H_EntityWithTexture_H_