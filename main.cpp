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


int main(int argc, char* argv[]) {

	GLFWwindow* window;

	if (!glfwInit()) {
		std::string noted;
		printf("glfw initiation failure\n Press Enter to Exit: \n");
		std::cin >> noted;

		exit(1);
	}
	//GB resolution is 160(w) x 144(h)
	window = glfwCreateWindow(160, 144, "daleGB pre-Alpha", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(2);
	}

	glfwTerminate();
	return 0;
}