#pragma once
#include <GL\glfw3.h>



namespace InputHandler {

	enum  KeyMode
	{
		RELEASE,
		PRESS,
		REPEAT,
		HOLDING
	};

	KeyMode __KeyInputMode;
	int __KeyPressed;
	
	void __KeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (__KeyInputMode == action || __KeyInputMode == KeyMode::HOLDING)
		{
			__KeyPressed = key;
		}

	}

	void Init(GLFWwindow * window)
	{
		glfwSetKeyCallback(window, __KeyHandler);
		__KeyInputMode = KeyMode::HOLDING;
	}
	void Init(GLFWwindow * window, KeyMode mode)
	{
		glfwSetKeyCallback(window, __KeyHandler);
		__KeyInputMode = mode;
	}

	
	int GetKey()
	{
		return __KeyPressed;
	}


};