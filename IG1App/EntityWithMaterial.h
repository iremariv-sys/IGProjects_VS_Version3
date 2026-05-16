//#include "Entity.h"
//#include "Material.h"
//
//class EntityWithMaterial : public Abs_Entity
//{
//public:
//	EntityWithMaterial();
//	virtual ~EntityWithMaterial() = default;
//
//	void render(const glm::mat4& modelViewMat) const override;
//
//	static void toggleShowNormals();
//
//protected:
//	Material mMaterial;
//
//private:
//	static bool mShowNormals;
//};
#ifndef _H_EntityWithMaterial_H_
#define _H_EntityWithMaterial_H_

#include "Entity.h"
#include "Material.h"

class EntityWithMaterial : public Abs_Entity
{
public:
	EntityWithMaterial();
	virtual ~EntityWithMaterial() = default;

	void render(const glm::mat4& modelViewMat) const override;

	static void toggleShowNormals();

	void setMaterial(const Material& material) { mMaterial = material; }
	Material& material() { return mMaterial; }
	const Material& material() const { return mMaterial; }

protected:
	Material mMaterial;

private:
	static bool mShowNormals;
};

#endif //_H_EntityWithMaterial_H_