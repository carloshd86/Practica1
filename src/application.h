#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "windowmanager.h"
#include "eventmanager.h"


class Application {

public:

	~Application();

	static Application * Instance();

	bool Init();
	bool End();

	IWindowManager * GetWindowManager();
	IEventManager  * GetEventManager();

private:

	Application();

	static Application *mInstance;

	bool             mInitialized; 
	IWindowManager  *mWindowManager;
	IEventManager   *mEventManager;
};


#endif // !__APPLICATION_H__

