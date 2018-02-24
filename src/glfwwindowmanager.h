#pragma once

#include "windowmanager.h"


class GlfwWindowManager : public IWindowManager {

public:

	static GlfwWindowManager * Instance();
	~GlfwWindowManager();

	virtual WM_Err Init ();
	virtual WM_Err End  ();

	virtual double        GetTime           () const;
	virtual bool          WindowShouldClose ();
	virtual void          GetWindowSize     (int& screenWidth, int& screenHeight);
	virtual void          SetViewport       (int x, int y, int width, int height);
	virtual void          SetResolution     (int width, int height);
	virtual void          SwapBuffers       ();
	virtual void          PollEvents        ();
	
	virtual void SetMouseMoveCallback  (WindowMouseMoveFun fun);
	virtual void SetMouseClickCallback (WindowMouseClickFun fun);
	virtual void SetKeyPressedCallback (WindowKeyFun fun);

private:
	GlfwWindowManager();

	static GlfwWindowManager *mInstance;
	Window                    mWindow;

	bool mInitialized;
};