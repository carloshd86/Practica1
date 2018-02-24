#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif


#include "inputmanager.h"
#include "ugine.h"
#include "globals.h"
#include <iostream>
#include <vector>


using namespace std;

int main() {
	// Inicializamos GLFW
	if (!glfwInit()) {
		cout << "Error: No se ha podido inicializar GLFW" << endl;
		return -1;
	}
	atexit(glfwTerminate);

	// Bucle principal
	double lastTime = glfwGetTime();
	Vec2 screenSize;

	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// Actualizamos delta
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// Actualizamos tama�o de ventana
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		lgfx_setviewport(0, 0, screenWidth, screenHeight);
		lgfx_setresolution(SCREEN_WIDTH_RESOLUTION, SCREEN_HEIGHT_RESOLUTION);
		screenSize.x = static_cast<float>(SCREEN_WIDTH_RESOLUTION);
		screenSize.y = static_cast<float>(SCREEN_HEIGHT_RESOLUTION);

		/********************************/

		// Actualizacion de logica del programa
		

		/********************************/

		// Pintado

		lgfx_setcolor(1.0f, 1.0f, 1.0f, 1.0f);
	
		/********************************/

		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	return 0;
}
