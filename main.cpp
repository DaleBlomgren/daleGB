///////////////////////////////////////////////////////////////////////////////
// DaleGB																	 //
//---------------------------------------------------------------------------//
// A Gameboy Emulator implemented in C++ with the help of GLFW				 //	
//---------------------------------------------------------------------------//
// Written by Dale Blomgren													 //
//---------------------------------------------------------------------------//
//																			 //
///////////////////////////////////////////////////////////////////////////////

#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>


int main(int argc, char* argv[]) {

	if (!glfwInit()) {
		std::string noted;
		printf("glfw initiation failure\n Press Enter to Exit: \n");
		std::cin >> noted;
		glfwTerminate();
		exit(1);
	}

	glfwTerminate();
	return 0;
}