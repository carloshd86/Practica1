#include "glfwwindowmanager.h"
#include "globals.h"
#include "asserts.h"

#define LITE_GFX_IMPLEMENTATION
#include <litegfx.h>

#define mGlfwWindow static_cast<GLFWwindow * >(mWindow.pWindow)


// *************************************************
//
// *************************************************

GlfwWindowManager * GlfwWindowManager::mInstance;

// *************************************************
//
// *************************************************

GlfwWindowManager::GlfwWindowManager() :
	mInitialized (false) {}

// *************************************************
//
// *************************************************

GlfwWindowManager::~GlfwWindowManager() {
	if (mInitialized)
		End();
}

// *************************************************
//
// *************************************************

GlfwWindowManager * GlfwWindowManager::Instance() {
	if (!mInstance) {
		mInstance = new GlfwWindowManager();
		mInstance->Init();
	}

	return mInstance;
}

// *************************************************
//
// *************************************************

IWindowManager::WM_Err GlfwWindowManager::Init() {

	// Init glfw
	if (!glfwInit())
		return KO;

	// Creating the window
	glfwWindowHint(GLFW_RESIZABLE, true);
	GLFWwindow* glfwWindow = glfwCreateWindow(GlobalConstants::SCREEN_WIDTH, GlobalConstants::SCREEN_HEIGHT, "Interfaz Usuario | GlfwInputManager", nullptr, nullptr);
	if (!glfwWindow)
		return KO;

	// Activating OpenGL
	glfwMakeContextCurrent(glfwWindow);

	// Initializing LiteGFX
	lgfx_setup2d(GlobalConstants::SCREEN_WIDTH, GlobalConstants::SCREEN_HEIGHT);

	mWindow.pWindow = glfwWindow;

	mInitialized = true;
	return OK;
}

// *************************************************
//
// *************************************************

IWindowManager::WM_Err GlfwWindowManager::End() {
	if (mInitialized)
		glfwTerminate();
	return OK;
}

// *************************************************
//
// *************************************************

double GlfwWindowManager::GetTime() const {
	return glfwGetTime();
}

// *************************************************
//
// *************************************************

bool  GlfwWindowManager::WindowShouldClose() {

	return glfwWindowShouldClose(mGlfwWindow);
}

// *************************************************
//
// *************************************************

void  GlfwWindowManager::GetWindowSize(int& screenWidth, int& screenHeight) {
	glfwGetWindowSize(mGlfwWindow, &screenWidth, &screenHeight);
}

// *************************************************
//
// *************************************************

void  GlfwWindowManager::SetViewport(int x, int y, int width, int height) {
	lgfx_setviewport(x, y, width, height);
}

// *************************************************
//
// *************************************************

void  GlfwWindowManager::SetResolution(int width, int height) {
	lgfx_setresolution(width, height);
}

// *************************************************
//
// *************************************************

void  GlfwWindowManager::SetColor(float r, float g, float b, float a) {
	lgfx_setcolor(r, g, b, a);
}

// *************************************************
//
// *************************************************

void  GlfwWindowManager::SwapBuffers() {
	glfwSwapBuffers(mGlfwWindow);	
}

// *************************************************
//
// *************************************************

void  GlfwWindowManager::PollEvents() {
	glfwPollEvents();
}

// *************************************************
//
// *************************************************

void  GlfwWindowManager::WaitEvents() {
	glfwWaitEvents();
}

// *************************************************
//
// *************************************************

void GlfwWindowManager::DrawRect(float x, float y, float width, float height) {
	lgfx_drawrect(x, y, width, height);
}

// *************************************************
//
// *************************************************
void GlfwWindowManager::ClearColorBuffer(float r, float g, float b) {
	lgfx_clearcolorbuffer(r, g, b);
}

// *************************************************
//
// *************************************************

void GlfwWindowManager::SetMouseMoveCallback(GLFWcursorposfun fun) {
	glfwSetCursorPosCallback(mGlfwWindow, fun);
}

// *************************************************
//
// *************************************************

void GlfwWindowManager::SetMouseClickCallback(GLFWmousebuttonfun fun) {
	glfwSetMouseButtonCallback(mGlfwWindow, fun);
}

// *************************************************
//
// *************************************************

void GlfwWindowManager::SetKeyPressedCallback(GLFWkeyfun fun) {
	glfwSetKeyCallback(mGlfwWindow, fun);
}