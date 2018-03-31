#pragma once

#include "eventmanager.h"
#include <map>
#include <vector>
#include "glfwwindowmanager.h"

class GlfwInputManager : public IEventManager {
	
public:

	typedef std::map<TEvent, std::multimap<int, IListener *>> ListenerMap;

	static GlfwInputManager * Instance();
	~GlfwInputManager();

	EM_Err Init();
	EM_Err End();

	EM_Err Register     (IListener * listener, TEvent e, int priority);
	EM_Err Unregister   (IListener * listener, TEvent e = TEvent::EAll);

	ListenerMap& GetListenerMap();

	static void MouseMove (GLFWwindow * window, double xpos, double ypos);
	static void MouseClick(GLFWwindow * window, int button, int action, int mods);
	static void KeyPressed(GLFWwindow * window, int key, int scancode, int action, int mods);

private:
	GlfwInputManager();

	static GlfwInputManager *mInstance;

	ListenerMap         mListeners;
	Window             *m_pWindow;
	GlfwWindowManager  *m_pWindowManager;
	bool                mInitialized;

	void RemoveListenerForEvent(IListener * listener, TEvent e);
};