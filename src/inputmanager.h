#pragma once

#include "eventmanager.h"
#include <map>
#include <vector>
#include "windowmanager.h"

class InputManager : public IEventManager {
	
public:

	typedef std::map<TEvent, std::map<int, std::vector<IListener *>>> ListenerMap;

	static InputManager * Instance();
	~InputManager();

	EM_Err Init();
	EM_Err End();

	EM_Err Register     (IListener * listener, TEvent e, int priority);
	EM_Err Unregister   (IListener * listener, TEvent e = TEvent::EAll);

	void MouseMove (double xpos, double ypos);
	void MouseClick(int button, int action, int mods);
	void KeyPressed(int key, int scancode, int action, int mods);

private:
	InputManager();

	static InputManager *mInstance;

	ListenerMap     mListeners;
	Window         *m_pWindow;
	IWindowManager *m_pWindowManager;
	bool            mInitialized;
};