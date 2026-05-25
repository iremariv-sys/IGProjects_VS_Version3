#include "Mesh.h"

using namespace std;
using namespace glm;

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = numeric_limits<GLuint>::max();

Mesh::Mesh()
	:mVAO(NONE)
	,mVBO(NONE)
	,mCBO(NONE)
	,mTCO(NONE)
	,mTBO(NONE)
	,mNBO(NONE) //apartado 57
{
}

Mesh::~Mesh()
{
	unload();
}

void
Mesh::draw() const
{
	glDrawArrays(
		mPrimitive,
		0,
		size()); // primitive graphic, first index and number of elements to be rendered
}

void
Mesh::load()
{
	assert(mVBO == NONE); // not already loaded
	if (vVertices.size() > 0) { // transfer data
		glGenBuffers(1, &mVBO);
		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, vVertices.size() * sizeof(vec3), vVertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), nullptr);
		glEnableVertexAttribArray(0);

		if (vColors.size() > 0) {             // upload colors
			glGenBuffers(1, &mCBO);

			glBindBuffer(GL_ARRAY_BUFFER, mCBO);
			glBufferData(GL_ARRAY_BUFFER, vColors.size() * sizeof(vec4), vColors.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), nullptr);
			glEnableVertexAttribArray(1);

		}
		//apartado 57: upload normales
		if (vNormals.size() > 0) {
			glGenBuffers(1, &mNBO);
			glBindBuffer(GL_ARRAY_BUFFER, mNBO);
			glBufferData(
				GL_ARRAY_BUFFER,
				vNormals.size() * sizeof(vec3),
				vNormals.data(),
				GL_STATIC_DRAW);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
				sizeof(vec3), nullptr);
			glEnableVertexAttribArray(3);
		}

		// ---- TEXTURE COORDS ----
		if (vTexCoords.size() > 0) {

			glGenBuffers(1, &mTCO);
			glBindBuffer(GL_ARRAY_BUFFER, mTCO);
			glBufferData(GL_ARRAY_BUFFER,
				vTexCoords.size() * sizeof(vec2),
				vTexCoords.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
				sizeof(vec2), nullptr);
			glEnableVertexAttribArray(2);

		}

		

		glBindVertexArray(0);
	}
	
}

void
Mesh::unload()
{
	if (mVAO != NONE) {
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
		mVAO = NONE;
		mVBO = NONE;

		if (mCBO != NONE) {
			glDeleteBuffers(1, &mCBO);
			mCBO = NONE;
		}

		if (mTBO != NONE) {
			glDeleteBuffers(1, &mTBO);
			mTBO = NONE;
		}
		if(mTCO != NONE) glDeleteBuffers(1, &mTCO);

		if (mNBO != NONE) {
			glDeleteBuffers(1, &mNBO);
			mNBO = NONE;
		}
	}
}

void
Mesh::render() const
{
	assert(mVAO != NONE);

	glBindVertexArray(mVAO);
	draw();
}

Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* Mesh::generateRegularPolygon(GLuint num, GLdouble r)
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_LINE_LOOP;
	mesh->mNumVertices = num;

	mesh->vVertices.reserve(num);

	double angulo = 90.0;              // grados
	double incremento = 360.0 / num;   // grados

	for (GLuint i = 0; i < num; ++i)
	{
		double rad = glm::radians(angulo);

		double x = r * cos(rad);
		double y = r * sin(rad);

		mesh->vVertices.emplace_back(x, y, 0.0);

		angulo += incremento;
	}


	return mesh;
}


//APARTADO 7, 8  - QUEREMOS PONERLE COLOR Y HACER LA FORMA DEL TRIANGULO 
Mesh* Mesh::generateRGBTriangle(GLdouble r) { // generaos el triangulo pero tambien le damos colors 
	Mesh* m = new Mesh();
	m->mPrimitive = GL_TRIANGLES;
	m->mNumVertices = 3;


	m->vVertices.push_back(glm::vec3(0, r, 0));        // Superior
	m->vVertices.push_back(glm::vec3(-r, -r, 0));      // Inferior Izquierda
	m->vVertices.push_back(glm::vec3(r, -r, 0));       // Inferior Derecha

	m->vColors.push_back(glm::vec4(1, 0, 0, 1));       // Rojo
	m->vColors.push_back(glm::vec4(0, 1, 0, 1));       // Verde
	m->vColors.push_back(glm::vec4(0, 0, 1, 1));       // Azul

	return m;
}

Mesh* Mesh::generateRGBRectangle(GLdouble w, GLdouble h) {
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP; // strip para optimizar ( 4 vértices para 2 triángulos)
	mesh->mNumVertices = 4;

	GLdouble x = w / 2.0;
	GLdouble y = h / 2.0;

	// Vértices (Posiciones)
	mesh->vVertices.push_back(glm::vec3(-x, y, 0.0)); // Superior Izquierda
	mesh->vVertices.push_back(glm::vec3(-x, -y, 0.0)); // Inferior Izquierda
	mesh->vVertices.push_back(glm::vec3(x, y, 0.0)); // Superior Derecha
	mesh->vVertices.push_back(glm::vec3(x, -y, 0.0)); // Inferior Derecha


	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0); // V0: 
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); // V1: 
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0); // V2: 
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);//V3 



	return mesh;
}


Mesh* Mesh::generateRGBCubeTriangles(GLdouble length)
{
	GLfloat l = GLfloat(length / 2.0f);

	glm::vec4 rojo = { 1, 0, 0, 1 };
	glm::vec4 verde = { 0, 1, 0, 1 };
	glm::vec4 azul = { 0, 0, 1, 1 };

	std::vector<glm::vec3> vertices = {
		{-l,-l, l}, { l,-l, l}, { l, l, l},
		{-l,-l, l}, { l, l, l}, {-l, l, l},

		{ l,-l,-l}, {-l,-l,-l}, {-l, l,-l},
		{ l,-l,-l}, {-l, l,-l}, { l, l,-l},

		{-l,-l,-l}, {-l,-l, l}, {-l, l, l},
		{-l,-l,-l}, {-l, l, l}, {-l, l,-l},

		{ l,-l, l}, { l,-l,-l}, { l, l,-l},
		{ l,-l, l}, { l, l,-l}, { l, l, l},

		{-l, l, l}, { l, l, l}, { l, l,-l},
		{-l, l, l}, { l, l,-l}, {-l, l,-l},

		{-l,-l,-l}, { l,-l,-l}, { l,-l, l},
		{-l,-l,-l}, { l,-l, l}, {-l,-l, l}
	};

	std::vector<glm::vec4> colors = {
		rojo, rojo, rojo, rojo, rojo, rojo,
		rojo, rojo, rojo, rojo, rojo, rojo,
		verde, verde, verde, verde, verde, verde,
		verde, verde, verde, verde, verde, verde,
		azul, azul, azul, azul, azul, azul,
		azul, azul, azul, azul, azul, azul
	};

	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLES;
	mesh->mNumVertices = GLuint(vertices.size());
	mesh->vVertices = vertices;
	mesh->vColors = colors;

	return mesh;
};




Mesh* Mesh::generaRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* m = new Mesh();

	m->mPrimitive = GL_TRIANGLE_STRIP;
	m->mNumVertices = 4;

	GLdouble x = w / 2.0;
	GLdouble z = h / 2.0;

	// Vértices en plano XZ (suelo)
	m->vVertices = {
		{-x, 0.0, -z},   // V0
		{-x, 0.0,  z},   // V1
		{ x, 0.0, -z},   // V2
		{ x, 0.0,  z}    // V3
	};

	// Coordenadas de textura repetidas rw × rh
	m->vTexCoords = {
		{0.0,    0.0},     // V0
		{0.0,    rh},      // V1
		{rw,     0.0},     // V2
		{rw,     rh}       // V3
	};

	return m;
}

// Apartado 22: Generar un cubo con líneas 


	//Mesh* Mesh::generateBoxOutline(GLdouble length)
	//{
	//	Mesh* m = new Mesh();
	//	m->mPrimitive = GL_TRIANGLE_STRIP;
	//	m->mNumVertices = 10;

	//	double h = length / 2.0;

	//	glm::vec3 V0(-h, h, h);
	//	glm::vec3 V1(h, h, h);
	//	glm::vec3 V2(h, h, -h);
	//	glm::vec3 V3(-h, h, -h);
	//	glm::vec3 V4(-h, -h, h);
	//	glm::vec3 V5(h, -h, h);
	//	glm::vec3 V6(h, -h, -h);
	//	glm::vec3 V7(-h, -h, -h);

	//	m->vVertices = {
	//		V0, V4,
	//		V1, V5,
	//		V2, V6,
	//		V3, V7,
	//		V0, V4
	//	};

	//	return m;
	//}


Mesh* Mesh::generateBoxOutlineTexCor(GLdouble length)
{
	Mesh* m = new Mesh();
	m->mPrimitive = GL_TRIANGLES;
	m->mNumVertices = 24; // 4 caras laterales × 6 vértices (sin tapa ni piso)

	double h = length / 2.0;

	glm::vec3 V0(-h, -h, h);
	glm::vec3 V1(h, -h, h);
	glm::vec3 V2(h, -h, -h);
	glm::vec3 V3(-h, -h, -h);
	glm::vec3 V4(-h, h, h);
	glm::vec3 V5(h, h, h);
	glm::vec3 V6(h, h, -h);
	glm::vec3 V7(-h, h, -h);

	m->vVertices = {
		// cara frontal
		V4, V5, V1, V4, V1, V0,
		// cara trasera
		V6, V7, V3, V6, V3, V2,
		// izquierda
		V7, V4, V0, V7, V0, V3,
		// derecha
		V5, V6, V2, V5, V2, V1,
		// superior
		//V7, V6, V5, V7, V5, V4,
		// inferior ( el piso lo gestiona Box)
		//V0, V1, V2, V0, V2, V3
	};

	m->vTexCoords = {
		// cada cara: V invertido (0=abajo, 1=arriba imagen derecha)
		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
		{0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},

		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
		{0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},

		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
		{0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},

		//{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
		//{0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},

		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
		{0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},

		//{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
		//{0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
	};

	return m;
}

//Apartado 26
Mesh* Mesh::generateStar3D(GLdouble re, GLuint np, GLdouble h)
{
	assert(np >= 3); 
	Mesh* m = new Mesh();
	m->mPrimitive = GL_TRIANGLE_FAN;

	// vertice central en el origen
	m->vVertices.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

	float outer = float(re);
	float inner = outer * 0.5f;
	float step = glm::radians(360.0f) / (np * 2.0f);

	for (GLuint i = 0; i < np * 2; ++i) {
		float angle = i * step;
		float radius = (i % 2 == 0) ? outer : inner;
		float x = radius * cosf(angle);
		float y = radius * sinf(angle);
		m->vVertices.push_back(glm::vec3(x, y, float(h)));
	}

	m->vVertices.push_back(m->vVertices[1]);

	m->mNumVertices = GLuint(m->vVertices.size());
	return m;
}
// Apartado 29
Mesh* Mesh::generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h)
{
	assert(np >= 3);
	Mesh* m = new Mesh();
	m->mPrimitive = GL_TRIANGLE_FAN;

	float outer = float(re);
	float inner = outer * 0.5f;
	float step = glm::radians(360.0f) / float(np * 2);

	// Centro en el origen z=0 (igual que generateStar3D)
	m->vVertices.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	m->vTexCoords.push_back(glm::vec2(0.5f, 0.5f));

	for (GLuint i = 0; i < np * 2; ++i) {
		float angle = float(i) * step;
		float radius = (i % 2 == 0) ? outer : inner;
		float x = radius * cosf(angle);
		float y = radius * sinf(angle);
		m->vVertices.push_back(glm::vec3(x, y, float(h)));

		float normR = radius / outer;
		m->vTexCoords.push_back(glm::vec2(
			0.5f + 0.5f * normR * cosf(angle),
			0.5f + 0.5f * normR * sinf(angle)
		));
	}

	// Cerrar 
	m->vVertices.push_back(m->vVertices[1]);
	m->vTexCoords.push_back(m->vTexCoords[1]);

	m->mNumVertices = GLuint(m->vVertices.size());
	return m;
}
