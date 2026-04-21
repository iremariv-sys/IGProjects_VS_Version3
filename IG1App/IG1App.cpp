#include "IG1App.h"
#include <iostream>
#include <thread>
#include "ColorMaterialEntity.h"

using namespace std;

// static single instance (singleton pattern)
IG1App IG1App::s_ig1app; // default constructor (constructor with no parameters)

// Print OpenGL errors and warnings
void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam)
{
	const char* prefix = (type == GL_DEBUG_TYPE_ERROR)
		? "\x1b[31m[ERROR]\x1b[0m "
		: "\x1b[33m[WARNING]\x1b[0m ";
	cout << prefix << message << endl;
}

// Print GLFW errors
void glfwErrorCallback(int error_code, const char* description)
{
	cout << "\x1b[33m[GLFW]\x1b[0m " << description << endl;
}

void
IG1App::close()
{
	cout << "Closing GLFW...\n";
	glfwSetWindowShouldClose(mWindow, true); // stops main loop
}

void
IG1App::run() // enters the main event processing loop
{
	if (mWindow == 0) // if not intilialized
		init();

	// IG1App main loop
	while (!glfwWindowShouldClose(mWindow)) {
		// Redisplay the window if needed
		if (mNeedsRedisplay) {
			display();
			mNeedsRedisplay = false;
		}

		// Stop and wait for new events
 	glfwWaitEvents();
	}

	destroy();
}

void
IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH);
	mCamera = new Camera(mViewPort);
	mCamera2 = new Camera(mViewPort);
	mScenes.push_back(new Scene);
	mScenes.push_back(new Scene1);
	mScenes.push_back(new Scene2);
	mScenes.push_back(new Scene3);
	mScenes.push_back(new Scene4);
	mScenes.push_back(new Scene5);
	mScenes.push_back(new Scene6);
	mScenes.push_back(new Scene7);
	mScenes.push_back(new Scene8);
	mScenes.push_back(new Scene9);

	mCamera->set2D();
	mCamera2->set2D();

	mScenes[0]->init();
	mScenes[1]->init();
	mScenes[2]->init();
	mScenes[3]->init();
	mScenes[4]->init();
	mScenes[5]->init();
	mScenes[6]->init();
	mScenes[7]->init();
	mScenes[8]->init();
	mScenes[9]->init();
	//mScenes[mCurrentScene]->load();

	// Cargar todas en GPU 
	mScenes[0]->load();
	mScenes[1]->load();
	mScenes[2]->load();
	mScenes[3]->load();
	mScenes[4]->load();
	mScenes[5]->load();
	mScenes[6]->load();
	mScenes[7]->load();
	mScenes[8]->load();
	mScenes[9]->load();
}
void
IG1App::iniWinOpenGL()
{ // Initialization
	cout << "Starting GLFW...\n";

	glfwSetErrorCallback(glfwErrorCallback);
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // enable on macOS
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Create window with its associated OpenGL context, return window's pointer
	mWindow = glfwCreateWindow(mWinW, mWinH, "IG1App", nullptr, nullptr);

	if (mWindow == nullptr) {
		glfwTerminate();
		throw std::logic_error("cannot create GLFW window");
	}

	glfwMakeContextCurrent(mWindow);

	// Initialize OpenGL extension library
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		throw std::logic_error("Error while loading extensions");
	}

	// Callback registration
	glfwSetWindowSizeCallback(mWindow, s_resize);
	glfwSetCharCallback(mWindow, s_key);
	glfwSetKeyCallback(mWindow, s_specialkey);
	glfwSetWindowRefreshCallback(mWindow, s_display);

	// Apartado 51
	glfwSetMouseButtonCallback(mWindow, s_mouse);
	glfwSetCursorPosCallback(mWindow, s_motion);
	glfwSetScrollCallback(mWindow, s_mouseWheel);

	// Error message callback (all messages)
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0u, 0, GL_TRUE);
	glDebugMessageCallback(debugCallback, nullptr);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

void
IG1App::destroy()
{ 
	for (Scene* scene : mScenes)
		delete scene;
	mScenes.clear();

	delete mCamera;
	mCamera = nullptr;
	delete mCamera2;  mCamera2 = nullptr;
	delete mViewPort;
	mViewPort = nullptr;

	Shader::destroy();

	glfwTerminate();
}
//Apartado 49
//void IG1App::display() const
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	if (!m2Vistas)
//	{
//		// --- UNA SOLA VISTA ---
//		mViewPort->setSize(mWinW, mWinH);
//		mCamera->setSize(mWinW, mWinH);
//		mScenes[mCurrentScene]->render(*mCamera);
//	}
//	else
//	{
//		// --- DOS VISTAS ---
//
//		// 1) Vista izquierda: cámara 3D normal
//		mViewPort->setPos(0, 0);
//		mViewPort->setSize(mWinW / 2, mWinH);
//		mCamera->setSize(mWinW / 2, mWinH);
//		mScenes[mCurrentScene]->render(*mCamera);
//
//		// 2) Vista derecha: cámara cenital
//		Camera camCenital = *mCamera;   // copiar cámara actual
//		camCenital.setCenital();        // ponerla cenital
//
//		mViewPort->setPos(mWinW / 2, 0);
//		mViewPort->setSize(mWinW / 2, mWinH);
//		camCenital.setSize(mWinW / 2, mWinH);
//
//		mScenes[mCurrentScene]->render(camCenital);
//	}
//
//	glfwSwapBuffers(mWindow);
//}


// aparatdo 52
void IG1App::display() const
{
 if (!m2Vistas && mCurrentScene == 8)
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	else
		glClearColor(0.6f, 0.7f, 0.8f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!m2Vistas)
	{
		mViewPort->setPos(0, 0);
		mViewPort->setSize(mWinW, mWinH);
		mCamera->setSize(mWinW, mWinH);
		mScenes[mCurrentScene]->render(*mCamera);
	}
	else
	{
		// Izquierda: Escena 4 con mCamera (3D)
		mViewPort->setPos(0, 0);
		mViewPort->setSize(mWinW / 2, mWinH);
		mCamera->setSize(mWinW / 2, mWinH);
		mScenes[4]->render(*mCamera);

		// Derecha: Escena 2 con mCamera2 (2D, persistente)
		mViewPort->setPos(mWinW / 2, 0);
		mViewPort->setSize(mWinW / 2, mWinH);
		mCamera2->setSize(mWinW / 2, mWinH);
		mScenes[2]->render(*mCamera2);
	}

	glfwSwapBuffers(mWindow);
}

/*/IG1App::display() const
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer
	
	mScenes[mCurrentScene]->render(*mCamera); // uploads the viewport and camera to the GPU

	glfwSwapBuffers(mWindow); // swaps the front and back buffer
}/**/

void
IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth;
	mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}
void IG1App::key(unsigned int key)
{
	bool need_redisplay = true;
	Camera* camera = activeCamera();

	switch (key) {

	case '+':
		camera->setScale(+0.01);
		break;

	case '-':
		camera->setScale(-0.01);
		break;

	case 'l':
		camera->set3D();
		break;

	case 'o':
		camera->set2D();
		break;

	//case 'u':
	//	mScenes[mCurrentScene]->update();
	//	break;
	case 'u':
		mScenes[activeSceneIdx()]->update();  // escena del viewport bajo el cursor
		break;

	case 'U':
	{
		static bool anim = false;
		anim = !anim;

		// Capturar la escena activa AL PULSAR U, no en cada frame
		size_t animSceneIdx = activeSceneIdx();

		while (anim && !glfwWindowShouldClose(mWindow))
		{
			double frameStart = glfwGetTime();

			mScenes[animSceneIdx]->update(); // siempre la misma escena

			mNeedsRedisplay = true;
			display();
			glfwPollEvents();

			double elapsed = glfwGetTime() - frameStart;
			if (elapsed < 0.03)
				std::this_thread::sleep_for(
					std::chrono::duration<double>(0.03 - elapsed));
		}
		anim = false;
	}
	break;

	// MOVIMIENTO DE CÁMARA (APARTADO 40)
	case 'a':
		camera->moveLR(-10);
		break;

	case 'd':
		camera->moveLR(10);
		break;

	case 'w':
		camera->moveUD(10);
		break;

	case 's':
		camera->moveUD(-10);
		break;

	case 'W':
		camera->moveFB(10);
		break;

	case 'S':
		camera->moveFB(-10);
		break;

	//case 'p':
	//	mCamera->changePrj();//Cambiar la proyeccion Ortogonal a Perpectiva Apartado 43
	//	break;
	case 'p':
		activeCamera()->changePrj();          // proyección del viewport bajo el cursor
		break;
	case 'c':
		camera->setCenital();
		break;

	case 'k':
	case 'K':
		m2Vistas = !m2Vistas;
		mNeedsRedisplay = true;
		break;

	case 'F':
	{
		Scene4* s = dynamic_cast<Scene4*>(mScenes[mCurrentScene]);
		if (s && s->mPhoto)
			s->savePhoto();
	}
	case 'f':
	{
		Scene8* s8 = dynamic_cast<Scene8*>(mScenes[mCurrentScene]);
		if (s8 != nullptr)
			s8->rotate();
		break;
	}

	case 'g':
	{
		Scene8* s8 = dynamic_cast<Scene8*>(mScenes[mCurrentScene]);
		if (s8 != nullptr)
			s8->orbit();
		break;
	}
	break;
	//Apartado 46
	case GLFW_KEY_A:
		camera->orbit(-5, 0);
		mNeedsRedisplay = true;
		break;

	case GLFW_KEY_D:
		camera->orbit(5, 0);
		mNeedsRedisplay = true;
		break;

	case 'q':
		camera->orbit(0, 1);
		mNeedsRedisplay = true;
		break;

	case 'e':
		camera->orbit(0, -1);
		mNeedsRedisplay = true;
		break;
	case 'n':
	case 'N': // apartado 63
		ColorMaterialEntity::toggleShowNormals();
		mNeedsRedisplay = true;
		break;

	default:
		if (key >= '0' && key <= '9') {
			if (changeScene(key - '0')) break;
			cout << "[NOTE] There is no scene " << char(key) << ".\n";
		}
		need_redisplay = false;
		break;
	}

	if (need_redisplay)
		mNeedsRedisplay = true;
}



void IG1App::specialkey(int key, int scancode, int action, int mods)

{
	Camera* active = activeCamera();
	if (action == GLFW_RELEASE)
		return;

	bool need_redisplay = true;

	bool ctrl = (mods & GLFW_MOD_CONTROL) != 0;

	switch (key) {

	case GLFW_KEY_LEFT:
		if (ctrl)
			active->rollReal(-5);   // Ctrl + left right roll
		else
			active->yawReal(-5);    // left right yaw
		break;

	case GLFW_KEY_RIGHT:
		if (ctrl)
			active->rollReal(5);    // Ctrl + right right roll
		else
			active->yawReal(5);     // right right yaw
		break;

	case GLFW_KEY_UP:
		active->pitchReal(5);       // up right pitch
		break;

	case GLFW_KEY_DOWN:
		active->pitchReal(-5);      // down right pitch
		break;

	default:
		need_redisplay = false;
		break;
	}

	if (need_redisplay)
		mNeedsRedisplay = true;
}


bool
IG1App::changeScene(size_t sceneNr)
{
	if (sceneNr >= mScenes.size())
		return false;

	mCurrentScene = sceneNr; 
	return true;
}

// Apartado 51

void IG1App::mouse(int button, int state, int mods)
{
	if (state == GLFW_PRESS) {
		glfwGetCursorPos(mWindow, &mMouseCoord.x, &mMouseCoord.y);
		mMouseButt = button;
		// Guardar viewport donde se hizo click 
		mLeftVP = !m2Vistas || (mMouseCoord.x < mWinW / 2);
	}
	else {
		mMouseButt = -1;
	}
}

void IG1App::motion(double x, double y)
{
	glm::dvec2 newCoord = { x, y };
	glm::dvec2 delta = newCoord - mMouseCoord;
	mMouseCoord = newCoord;

	// Cámara del viewport donde se inició el drag 
	Camera* cam = mLeftVP ? mCamera : mCamera2;

	if (mMouseButt == GLFW_MOUSE_BUTTON_RIGHT) {
		cam->moveLR(static_cast<GLfloat>(-delta.x) * 0.5f);
		cam->moveUD(static_cast<GLfloat>(delta.y) * 0.5f);
		mNeedsRedisplay = true;
	}
	else if (mMouseButt == GLFW_MOUSE_BUTTON_LEFT) {
		cam->orbit(static_cast<GLfloat>(delta.x) * 0.5f,
			static_cast<GLfloat>(-delta.y) * 0.5f);
		mNeedsRedisplay = true;
	}
}

void IG1App::mouseWheel(double dx, double dy)
{
	bool ctrl = (glfwGetKey(mWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
		glfwGetKey(mWindow, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS);

	Camera* cam = activeCamera();  // viewport bajo el cursor

	if (ctrl)
		cam->setScale(dy * 0.01);
	else
		cam->moveFB(static_cast<GLfloat>(dy) * 10.0f);

	mNeedsRedisplay = true;
}
Camera* IG1App::activeCamera() const
{
	if (!m2Vistas) return mCamera;
	double cx, cy;
	glfwGetCursorPos(mWindow, &cx, &cy);
	return (cx < mWinW / 2) ? mCamera : mCamera2;
}

size_t IG1App::activeSceneIdx() const
{
	if (!m2Vistas) return mCurrentScene;
	double cx, cy;
	glfwGetCursorPos(mWindow, &cx, &cy);
	return (cx < mWinW / 2) ? 4u : 2u;
}

