#include "pch.h"

using namespace FieaGameEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	UNREFERENCED_PARAMETER(instance);
	UNREFERENCED_PARAMETER(previousInstance);
	UNREFERENCED_PARAMETER(commandLine);
	UNREFERENCED_PARAMETER(showCommand);

	//Creating an instance of the class defined in the Library

	//Initializing OpenGL and creating the window
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(640, 480, "Test Window", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}
