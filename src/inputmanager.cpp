#include "inputmanager.h"
#include "globals.h"
#include "glfwwindowmanager.h"


#define LITE_GFX_IMPLEMENTATION
#include "litegfx.h"

// Constructors

InputManager::InputManager() :
	m_initialized (false) {}


//Destructor

InputManager::~InputManager() {
	if (m_initalized)
		End();
}

// Public

InputManager * InputManager::Instance() {
	if (!m_instance) {
		m_instance = new InputManager();
		m_instance->Init();
	}

	return m_instance;
}

IEventManager::EM_Err InputManager::Init() {

	// Init glfw
	if (!glfwInit())
		return KO;

	// Creating the window
	glfwWindowHint(GLFW_RESIZABLE, true);
	GLFWwindow* glfwWindow = glfwCreateWindow(GlobalConstants::SCREEN_WIDTH, GlobalConstants::SCREEN_HEIGHT, "Interfaz Usuario | InputManager", nullptr, nullptr);
	if (!glfwWindow)
		return KO;

	// Activating OpenGL
	glfwMakeContextCurrent(GLFWWINDOW);

	// Seting glfw window user pointer to this InputManager
	glfwSetWindowUserPointer(glfwWindow, this);

	// Setting events
	// Mouse Move
	auto mouseMoveFunc = [](Window* window, double xpos, double ypos)
	{
		static_cast<InputManager*>(glfwGetWindowUserPointer(window))->MouseMove(window, xpos, ypos);
	};
	glfwSetCursorPosCallback(glfwWindow, mouseMoveFunc);

	// Mouse Click
	auto mouseClickFunc = [](Window* window, int button, int action, int mods)
	{
		static_cast<InputManager*>(glfwGetWindowUserPointer(window))->MouseClick(window, button, action, mods);
	};
	glfwSetMouseButtonCallback(glfwWindow, mouseClickFunc);
	
	// Mouse Click
	auto keyPressedFunc = [](Window* window, int key, int scancode, int action, int mods)
	{
		static_cast<InputManager*>(glfwGetWindowUserPointer(window))->KeyPressed(window, key, scancode, action, mods);
	};
	glfwSetKeyCallback(glfwWindow, keyPressedFunc);


	m_initialized = true;
	return OK;
}

IEventManager::EM_Err InputManager::End() {

	if (m_initialized)
		glfwTerminate();

	return OK;
}

IEventManager::EM_Err InputManager::Register(IListener * listener, TEvent e, int priority) {

	if (EAll == e)
		return KO;


	m_listeners[e][priority].push_back(listener);

	return OK;
}

IEventManager::EM_Err InputManager::Unregister(IListener *, TEvent e = TEvent::EAll) {

	return OK;
}

void InputManager::MouseMove(Window* window, double xpos, double ypos) {

	//glfwGetMouseButton
}

void InputManager::MouseClick(Window* window, int button, int action, int mods) {
	
	//glfwGetmouse
}

void InputManager::KeyPressed(Window* window, int key, int scancode, int action, int mods) {
	
}