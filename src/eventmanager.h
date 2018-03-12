#pragma once

class CEvent;
class Window;

class IEventManager {

public:

	enum EM_Err  {
		KO,
		OK
	};

	enum TEvent {
		ELeftClick,
		ERightClick,
		EMiddleClick,
		EKeyPressed,
		EAll
	};

	class IListener {

	public:

		virtual bool ProcessEvent(const CEvent &event) = 0;
	};


	virtual EM_Err Register   (IListener * listener, TEvent e, int priority)  = 0;
	virtual EM_Err Unregister (IListener * listener, TEvent e = TEvent::EAll) = 0;

	virtual void MouseMove  (double xpos, double ypos)                    = 0;
	virtual void MouseClick (int button, int action, int mods)            = 0;
	virtual void KeyPressed (int key, int scancode, int action, int mods) = 0;
};