#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif


#include "application.h"
#include "globals.h"
#include "vec2.h"
#include "asserts.h"
#include <iostream>
#include <vector>


using namespace std;

int main() {

	Application * pApplication = Application::Instance();
	ASSERT(pApplication);

	IWindowManager * pWindowManager = pApplication->GetWindowManager();
	ASSERT(pWindowManager);
	IEventManager  * pInputManager  = pApplication->GetEventManager();
	ASSERT(pInputManager);

	// Bucle principal
	double lastTime = pWindowManager->GetTime();
	int screenWidth, screenHeight;

	while (!pWindowManager->WindowShouldClose()) {
		// Actualizamos delta
		float deltaTime = static_cast<float>(pWindowManager->GetTime() - lastTime);
		lastTime = pWindowManager->GetTime();

		// Actualizamos tamaño de ventana
		pWindowManager->GetWindowSize(screenWidth, screenHeight);
		pWindowManager->SetViewport(0, 0, screenWidth, screenHeight);
		pWindowManager->SetResolution(GlobalConstants::SCREEN_WIDTH, GlobalConstants::SCREEN_HEIGHT);

		/********************************/

		// Actualizacion de logica del programa
		

		/********************************/

		// Pintado
		pWindowManager->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	
		/********************************/

		// Actualizamos ventana y eventos
		pWindowManager->SwapBuffers();
		//pWindowManager->PollEvents();
	}


	return 0;
}
