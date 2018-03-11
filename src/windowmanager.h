#ifndef __WINDOW_MANAGER_H__
#define __WINDOW_MANAGER_H__

#include <functional>


class IWindowManager {

public:

	enum WM_Err  {
		KO,
		OK
	};

	class Window {
	public:
		void * pWindow;
	};

	typedef void (WindowMouseMoveFun)(double,double);
	typedef void (WindowMouseClickFun)(int,int,int);
	typedef void (WindowKeyFun)(int,int,int,int);

	virtual WM_Err Init ()  = 0;
	virtual WM_Err End  () = 0;

	virtual double        GetTime                  () const                                              = 0;
	virtual bool          WindowShouldClose        ()                                                    = 0;
	virtual void          GetWindowSize            (int& screenWidth, int& screenHeight)                 = 0;
	virtual void          SetViewport              (int x, int y, int width, int height)                 = 0;
	virtual void          SetResolution            (int width, int height)                               = 0;
	virtual void          SwapBuffers              ()                                                    = 0;
	virtual void          PollEvents               ()                                                    = 0;

	virtual void SetMouseMoveCallback  (std::function<WindowMouseMoveFun> fun)  = 0;
	virtual void SetMouseClickCallback (std::function<WindowMouseClickFun> fun) = 0;
	virtual void SetKeyPressedCallback (std::function<WindowKeyFun> fun)        = 0;

};

#endif