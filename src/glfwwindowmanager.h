#pragma once

#include "windowmanager.h"
#include <glfw3.h>


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
	virtual void          SetColor          (float r, float g, float b, float a);
	virtual void          SwapBuffers       ();
	virtual void          PollEvents        ();
	virtual void          WaitEvents        ();
	virtual void          DrawRect          (float x, float y, float width, float height);
	virtual void          ClearColorBuffer  (float r, float g, float b);
	
	virtual void SetMouseMoveCallback  (GLFWcursorposfun fun);
	virtual void SetMouseClickCallback (GLFWmousebuttonfun fun);
	virtual void SetKeyPressedCallback (GLFWkeyfun fun);

private:
	GlfwWindowManager();

	static GlfwWindowManager *mInstance;
	Window                    mWindow;

	bool mInitialized;
};