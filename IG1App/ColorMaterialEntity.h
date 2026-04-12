//#ifndef _H_ColorMaterialEntity_H_
//#define _H_ColorMaterialEntity_H_
//
//#include "SingleColorEntity.h"
//
//class ColorMaterialEntity : public SingleColorEntity
//{
//public:
//	ColorMaterialEntity(glm::vec4 color);
//	virtual void render(glm::mat4 const& modelViewMat) const override;
//};
//
//#endif //_H_ColorMaterialEntity_H_

// apartado 63

#ifndef _H_ColorMaterialEntity_H_
#define _H_ColorMaterialEntity_H_

#include "SingleColorEntity.h"

class ColorMaterialEntity : public SingleColorEntity
{
public:
	ColorMaterialEntity(glm::vec4 color);

	virtual void render(glm::mat4 const& modelViewMat) const override;

	static void toggleShowNormals();

private:
	static bool mShowNormals;
};

#endif //_H_ColorMaterialEntity_H_