#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

class Mesh
{
public:
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh
	static Mesh* generateRegularPolygon(GLuint num, GLdouble r);
	static Mesh* generateRGBTriangle(GLdouble r); //APARTADO 7
	//static Mesh* generateRectangle(GLdouble w, GLdouble h);
	static Mesh* generateRGBRectangle(GLdouble w, GLdouble h); //APARTADO 8
	//static Mesh* generateCube(GLdouble length);
	static Mesh* generateRGBCubeTriangles(GLdouble length); //encena 3
	//static Mesh* generateRectangleTexCor(GLdouble w, GLdouble h); //apartado 20
	static Mesh* generaRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh); //apartado 21
	static Mesh* generateBoxOutline(GLdouble length); //apartado 22
	static Mesh* generateBoxOutlineTexCor(GLdouble length); //apartado 24
	static Mesh* generateStar3D(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h); //apartado 29

	Mesh();
	virtual ~Mesh();

	Mesh(const Mesh& m) = delete;            // no copy constructor
	Mesh& operator=(const Mesh& m) = delete; // no copy assignment

	virtual void render() const;

	GLuint size() const { return mNumVertices; }; // number of elements
	std::vector<glm::vec3> const& vertices() const { return vVertices; };
	std::vector<glm::vec4> const& colors() const { return vColors; };
	std::vector<glm::vec2> const& texCoords() const { return vTexCoords; };

	void load();
	void unload();

protected:
	GLuint mPrimitive =
	  GL_TRIANGLES;          // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	
	GLuint mNumVertices = 0; // number of elements ( = vVertices.size())
	std::vector<glm::vec3> vVertices; // vertex array
	std::vector<glm::vec4> vColors;   // color array
	std::vector<glm::vec2> vTexCoords; // Añadido: coordenadas de textura
	virtual void draw() const;

	GLuint mVAO;  // vertex array object

private:
	GLuint mVBO;  // vertex buffer object
	GLuint mCBO;  // color buffer object
	GLuint mTBO;  // texture coordinate buffer object (añadido)
	GLuint mTCO;
};

#endif //_H_Scene_H_
