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

	void MouseMove (double xpos, double ypos);
	void MouseClick(int button, int action, int mods);
	void KeyPressed(int key, int scancode, int action, int mods);

private:
	GlfwInputManager();

	static GlfwInputManager *mInstance;

	ListenerMap     mListeners;
	Window         *m_pWindow;
	IWindowManager *m_pWindowManager;
	bool            mInitialized;

	float mMouseXPos;
	float mMouseYPos;

	int mMouseButton;
	int mMouseAction;
	int mMouseMods;

	int mKey;
	int mKeyScanCode;
	int mKeyAction;
	int mKeyMods;
};