#ifndef _H_IG1App_H_
#define _H_IG1App_H_

#include <glad/glad.h>    // OpenGL loader library
#include <GLFW/glfw3.h>  // OpenGL Library
#include <glm/glm.hpp>   // OpenGL Mathematics
#include "Material.h"
#include "Camera.h"
#include "Scene.h"
#include "Viewport.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scene6.h"
#include "Scene7.h"

class IG1App
{
public:
	// static single instance (singleton pattern)
	static IG1App s_ig1app;

	IG1App(IG1App const& J) = delete;         // no copy constructor
	void operator=(IG1App const& J) = delete; // no copy assignment

	// Viewport position and size
	Viewport const& viewPort();
	// Camera position, view volume and projection
	Camera const& camera();
	// Graphics objects of the scene
	Scene const& scene();


	// Change to the given scene
	bool changeScene(size_t sceneNr);

	void run();   // the main event processing loop
	void close(); // the application

protected:
	IG1App() = default;

	void init();
	void iniWinOpenGL();
	void destroy();

	void display() const;                      // the scene
	void resize(int newWidth, int newHeight);  // the viewport (without changing the scale)
	void key(unsigned int codepoint);          // keypress event
	void specialkey(int key, int scancode, int action, int mods); // special keypress event

	// Apartado 51
	void mouse(int button, int action, int mods);       // botón del ratón
	void motion(double x, double y);                    // movimiento del ratón
	void mouseWheel(double dx, double dy);

	// static callbacks
	static void s_display(GLFWwindow*) { s_ig1app.display(); };
	static void s_resize(GLFWwindow*, int newWidth, int newHeight) { s_ig1app.resize(newWidth, newHeight); };
	static void s_key(GLFWwindow* win, unsigned int codepoint) { s_ig1app.key(codepoint); };
	static void s_specialkey(GLFWwindow* win, int key, int scancode, int action, int mods) { s_ig1app.specialkey(key, scancode, action, mods); };
	
	// Apartado 51
	static void s_mouse(GLFWwindow* win, int button, int action, int mods) { s_ig1app.mouse(button, action, mods); };
	static void s_motion(GLFWwindow* win, double x, double y) { s_ig1app.motion(x, y); };
	static void s_mouseWheel(GLFWwindow* win, double dx, double dy) { s_ig1app.mouseWheel(dx, dy); };




	Camera* activeCamera() const;
	size_t  activeSceneIdx() const;

	bool m2Vistas = false;
	bool mLeftVP = true;   // viewport donde se hizo el último click

	Viewport* mViewPort = nullptr;
	Camera* mCamera = nullptr;  // viewport izquierdo (Escena 4, 3D)
	Camera* mCamera2 = nullptr;  // viewport derecho   (Escena 2, 2D)

	std::vector<Scene*> mScenes;
	size_t mCurrentScene = 0;

	bool         mNeedsRedisplay = true;
	GLFWwindow* mWindow = nullptr;
	int          mWinW = 800;
	int          mWinH = 600;

	glm::dvec2 mMouseCoord = { 0.0, 0.0 };
	int        mMouseButt = -1;


};

inline Viewport const&
IG1App::viewPort()
{
	return *mViewPort;
}

inline Camera const&
IG1App::camera()
{
	return *mCamera;
}

inline Scene const&
IG1App::scene()
{
	return *mScenes[mCurrentScene];
}

#endif //_H_IG1App_H_
