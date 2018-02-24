#pragma once

#include "eventmanager.h"
#include "windowmanager.h"
#include <map>
#include <vector>


class InputManager : public IEventManager {
	
public:

	typedef std::map<TEvent, std::map<int, std::vector<IListener *>>> ListenerMap;

	static InputManager * Instance();
	~InputManager();

	EM_Err Init();
	EM_Err End();

	EM_Err Register     (IListener * listener, TEvent e, int priority);
	EM_Err Unregister   (IListener * listener, TEvent e = TEvent::EAll);

	void MouseMove (IWindowManager::Window * window, double xpos, double ypos);
	void MouseClick(IWindowManager::Window * window, int button, int action, int mods);
	void KeyPressed(IWindowManager::Window * window, int key, int scancode, int action, int mods);

private:
	InputManager();

	static InputManager *m_instance;

	ListenerMap m_listeners;
	const void *m_window;
	bool        m_initialized;
};