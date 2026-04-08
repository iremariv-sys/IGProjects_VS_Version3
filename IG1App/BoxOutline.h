#ifndef _H_BoxOutline_H_
#define _H_BoxOutline_H_

#include "SingleColorEntity.h"
#include "Mesh.h"
#include "EntityWithTexture.h"

//class BoxOutline : public SingleColorEntity
class BoxOutline : public EntityWithTexture
{
public:
    //explicit BoxOutline(GLdouble length);
	//BoxOutline(Texture* tex, GLdouble length);
	BoxOutline(Texture* texExterior, Texture* texInterior, GLdouble length);
	void render(glm::mat4 const& modelViewMat) const override;


private:
	Texture* mInnerTexture = nullptr;
};

#endif //_H_BoxOutline_H_