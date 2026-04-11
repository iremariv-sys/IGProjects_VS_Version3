//#pragma once
//
//#include "Mesh.h"
//#include <vector>
//
//class IndexMesh : public Mesh
//{
//public:
//	IndexMesh();
//	virtual ~IndexMesh() override;
//
//	IndexMesh(const IndexMesh& m) = delete;
//	IndexMesh& operator=(const IndexMesh& m) = delete;
//
//	virtual void load() override;
//	virtual void unload() override;
//
//protected:
//	virtual void draw() const override;
//
//	std::vector<GLuint> vIndexes;
//
//private:
//	GLuint mIBO;
//};


#include "Mesh.h"
#include <numbers>

class IndexMesh : public Mesh
{
public:
	IndexMesh();
	virtual ~IndexMesh() override;

	static IndexMesh* generateByRevolution(
		const std::vector<glm::vec2>& profile,
		GLuint nSamples,
		GLfloat angleMax = 2.0f * std::numbers::pi_v<GLfloat>);

	void buildNormalVectors(); // Apartado 59

	IndexMesh(const IndexMesh& m) = delete;
	IndexMesh& operator=(const IndexMesh& m) = delete;

	virtual void load() override;
	virtual void unload() override;

protected:
	virtual void draw() const override;

	std::vector<GLuint> vIndexes;

private:
	GLuint mIBO;
};