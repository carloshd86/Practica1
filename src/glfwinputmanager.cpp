#include "glfwinputmanager.h"
#include "globals.h"
#include "glfwwindowmanager.h"
#include "asserts.h"

// Constructors

GlfwInputManager::GlfwInputManager() :
	mInitialized (false) {}


//Destructor

GlfwInputManager::~GlfwInputManager() {
	if (mInitialized)
		End();
}

// Public

GlfwInputManager * GlfwInputManager::Instance() {
	if (!mInstance) {
		mInstance = new GlfwInputManager();
		mInstance->Init();
	}

	return mInstance;
}

IEventManager::EM_Err GlfwInputManager::Init() {

	if (mInitialized)
		return OK;

	m_pWindowManager = GlfwWindowManager::Instance();

	ASSERT(m_pWindowManager);

	// Setting events
	// Mouse Move
	m_pWindowManager->SetMouseMoveCallback(std::bind(&GlfwInputManager::MouseMove, this, std::placeholders::_1, std::placeholders::_2));

	// Mouse Click
	m_pWindowManager->SetMouseClickCallback(std::bind(&GlfwInputManager::MouseClick, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	
	// Key Pressed
	m_pWindowManager->SetKeyPressedCallback(std::bind(&GlfwInputManager::KeyPressed, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));


	mInitialized = true;
	return OK;
}

IEventManager::EM_Err GlfwInputManager::End() {

	return OK;
}

IEventManager::EM_Err GlfwInputManager::Register(IListener * listener, TEvent e, int priority) {

	if (EAll == e)
		return KO;


	mListeners[e][priority].push_back(listener);

	return OK;
}

IEventManager::EM_Err GlfwInputManager::Unregister(IListener *, TEvent e = TEvent::EAll) {

	return OK;
}

void GlfwInputManager::MouseMove(double xpos, double ypos) {

	mMouseXPos = static_cast<float>(xpos);
	mMouseYPos = static_cast<float>(ypos);
}

void GlfwInputManager::MouseClick(int button, int action, int mods) {
	
	mMouseButton = button;
	mMouseAction = action;
	mMouseMods   = mods;
}

void GlfwInputManager::KeyPressed(int key, int scancode, int action, int mods) {

	mKey         = key;
	mKeyScanCode = scancode;
	mKeyAction   = action;
	mKeyMods     = mods;
}