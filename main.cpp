///////////////////////////////////////////////////////////////////////////////
// DaleGB																	 //
//---------------------------------------------------------------------------//
// A Gameboy Emulator implemented in C++ with the help of GLFW				 //	
//---------------------------------------------------------------------------//
// Written by Dale Blomgren													 //
//---------------------------------------------------------------------------//
//																			 //
///////////////////////////////////////////////////////////////////////////////

//#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144


static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description); 
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char* argv[]) {

	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		std::string noted;
		printf("glfw initiation failure\n Press Enter to Exit: \n");
		std::cin >> noted;

		exit(EXIT_FAILURE);
	}
	//GB resolution is 160(w) x 144(h)
	window = glfwCreateWindow(160, 144, "daleGB pre-Alpha", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);


	//Primary loop
	while (!glfwWindowShouldClose(window)) {

	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}