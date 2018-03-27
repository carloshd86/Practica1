#pragma once

#include "eventmanager.h"
#include <map>
#include <vector>
#include "windowmanager.h"

class GlfwInputManager : public IEventManager {
	
public:

	typedef std::map<TEvent, std::map<int, std::vector<IListener *>>> ListenerMap;

	static GlfwInputManager * Instance();
	~GlfwInputManager();

	EM_Err Init();
	EM_Err End();

	EM_Err Register     (IListener * listener, TEvent e, int priority);
	EM_Err Unregister   (IListener * listener, TEvent e = TEvent::EAll);

	static void MouseMove (void * window, double xpos, double ypos);
	static void MouseClick(void * window, int button, int action, int mods);
	static void KeyPressed(void * window, int key, int scancode, int action, int mods);

private:
	GlfwInputManager();

	static GlfwInputManager *mInstance;

	static ListenerMap  mListeners;
	Window             *m_pWindow;
	IWindowManager     *m_pWindowManager;
	bool                mInitialized;

	void RemoveListenerMapListenerForEvent(IListener * listener, TEvent e);
};