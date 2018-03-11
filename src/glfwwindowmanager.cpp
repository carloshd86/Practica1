#include "glfwwindowmanager.h"
#include "globals.h"
#include <glfw3.h>
#include "asserts.h"

#define LITE_GFX_IMPLEMENTATION
#include <litegfx.h>

#define mGlfwWindow static_cast<GLFWwindow * >(mWindow.pWindow)


// Constructors

GlfwWindowManager::GlfwWindowManager() :
	mInitialized (false) {}


//Destructor

GlfwWindowManager::~GlfwWindowManager() {
	if (mInitialized)
		End();
}

// Public

GlfwWindowManager * GlfwWindowManager::Instance() {
	if (!mInstance) {
		mInstance = new GlfwWindowManager();
		mInstance->Init();
	}

	return mInstance;
}


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

	// Seting glfw window user pointer to this GlfwInputManager
	glfwSetWindowUserPointer(glfwWindow, this);

	mInitialized = true;
	return OK;
}

IWindowManager::WM_Err GlfwWindowManager::End() {
	if (mInitialized)
		glfwTerminate();
	return OK;
}

double GlfwWindowManager::GetTime() const {
	return glfwGetTime();
}

bool  GlfwWindowManager::WindowShouldClose() {

	return glfwWindowShouldClose(mGlfwWindow);
}

void  GlfwWindowManager::GetWindowSize(int& screenWidth, int& screenHeight) {
	glfwGetWindowSize(mGlfwWindow, &screenWidth, &screenHeight);
}

void  GlfwWindowManager::SetViewport(int x, int y, int width, int height) {
	lgfx_setviewport(x, y, width, height);
}

void  GlfwWindowManager::SetResolution(int width, int height) {
	lgfx_setresolution(width, height);
}

void  GlfwWindowManager::SwapBuffers() {
	glfwSwapBuffers(mGlfwWindow);	
}

void  GlfwWindowManager::PollEvents() {
	glfwPollEvents();
}

void GlfwWindowManager::SetMouseMoveCallback(std::function<WindowMouseMoveFun> fun) {
	GLFWcursorposfun * glfwFun = fun.target<GLFWcursorposfun>();
	ASSERT(glfwFun);
	glfwSetCursorPosCallback(mGlfwWindow, *glfwFun);
}

void GlfwWindowManager::SetMouseClickCallback(std::function<WindowMouseClickFun> fun) {
	GLFWmousebuttonfun * glfwFun = fun.target<GLFWmousebuttonfun>();
	ASSERT(glfwFun);
	glfwSetMouseButtonCallback(mGlfwWindow, *glfwFun);
}

void GlfwWindowManager::SetKeyPressedCallback(std::function<WindowKeyFun> fun) {
	GLFWkeyfun * glfwFun = fun.target<GLFWkeyfun>();
	ASSERT(glfwFun);
	glfwSetKeyCallback(mGlfwWindow, *glfwFun);
}
