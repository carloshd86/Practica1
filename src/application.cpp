#include "application.h"
#include "glfwwindowmanager.h"
#include "glfwinputmanager.h"
#include "asserts.h"


Application * Application::mInstance;

// *************************************************
//
// *************************************************

Application::Application() :
	mInitialized   (false),
	mWindowManager (nullptr),
	mEventManager  (nullptr) {}

// *************************************************
//
// *************************************************

Application::~Application() {
	if (mInitialized)
		End();
}

// *************************************************
//
// *************************************************

Application * Application::Instance() {
	if (!mInstance) {
		mInstance = new Application();
		mInstance->Init();
	}

	return mInstance;
}

// *************************************************
//
// *************************************************

bool Application::Init() {
	if (mInitialized)
		return true;

	mWindowManager = GlfwWindowManager::Instance();
	ASSERT(mWindowManager)

	mEventManager  = GlfwInputManager::Instance();
	ASSERT(mEventManager)

	mInitialized  = true;

	return true;
}

// *************************************************
//
// *************************************************

bool Application::End() {

	delete mWindowManager;
	mWindowManager = nullptr;
	delete mEventManager;
	mEventManager = nullptr;

	mInitialized = false;

	return true;
}

// *************************************************
//
// *************************************************

IWindowManager * Application::GetWindowManager() {
	return mWindowManager;
}

// *************************************************
//
// *************************************************

IEventManager * Application::GetEventManager() {
	return mEventManager;
}

