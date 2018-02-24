#include "inputmanager.h"
#include "globals.h"
#include "glfwwindowmanager.h"
#include "asserts.h"

#define LITE_GFX_IMPLEMENTATION
#include "litegfx.h"

// Constructors

InputManager::InputManager() :
	mInitialized (false) {}


//Destructor

InputManager::~InputManager() {
	if (mInitalized)
		End();
}

// Public

InputManager * InputManager::Instance() {
	if (!mInstance) {
		mInstance = new InputManager();
		mInstance->Init();
	}

	return mInstance;
}

IEventManager::EM_Err InputManager::Init() {

	if (mInitialized)
		return OK;

	m_pWindowManager = GlfwWindowManager::Instance();

	ASSERT(m_pWindowManager);

	// Setting events
	// Mouse Move
	IWindowManager::WindowMouseMoveFun mouseMoveFunc = [this](double xpos, double ypos)
	{
		MouseMove(xpos, ypos);
	};
	m_pWindowManager->SetMouseMoveCallback(mouseMoveFunc);

	// Mouse Click
	IWindowManager::WindowMouseClickFun mouseClickFunc = [this](int button, int action, int mods)
	{
		MouseClick(button, action, mods);
	};
	m_pWindowManager->SetMouseClickCallback(mouseClickFunc);
	
	// Mouse Click
	IWindowManager::WindowKeyFun keyPressedFunc = [this](int key, int scancode, int action, int mods)
	{
		KeyPressed(key, scancode, action, mods);
	};
	m_pWindowManager->SetKeyPressedCallback(keyPressedFunc);


	mInitialized = true;
	return OK;
}

IEventManager::EM_Err InputManager::End() {

	return OK;
}

IEventManager::EM_Err InputManager::Register(IListener * listener, TEvent e, int priority) {

	if (EAll == e)
		return KO;


	mListeners[e][priority].push_back(listener);

	return OK;
}

IEventManager::EM_Err InputManager::Unregister(IListener *, TEvent e = TEvent::EAll) {

	return OK;
}

void InputManager::MouseMove(double xpos, double ypos) {

	//glfwGetMouseButton
}

void InputManager::MouseClick(int button, int action, int mods) {
	
	//glfwGetmouse
}

void InputManager::KeyPressed(int key, int scancode, int action, int mods) {
	
}