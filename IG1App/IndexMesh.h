#include "Mesh.h"
#include <numbers>

class IndexMesh : public Mesh
{
public:
	IndexMesh();
	virtual ~IndexMesh() override;
    static IndexMesh* generateIndexedBox(GLdouble l); // escena 6, apartado 64
	static IndexMesh* generateIndexedBox8(GLdouble l); // ecena 6, apartado 61
	static IndexMesh* generateSphere(GLdouble radius, GLuint nParallel, GLuint nMeridians);//apartado 65 scene7
	static IndexMesh* generateByRevolution(
		const std::vector<glm::vec2>& profile,
		GLuint nSamples,
     GLfloat angleMax = 2.0f * std::numbers::pi_v<GLfloat>,
		bool closedProfile = false);

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