#include "Game.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "scenes/GameScene.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

inline void Game::UpdateDeltaBegain()
{
	curFrame = std::chrono::steady_clock::now();
}

inline void Game::UpdateDeltaEnd()
{
	deltaTime = (double)(curFrame.time_since_epoch().count() - lastFrame.time_since_epoch().count())* 1e-9;
	FPS = 1.0 / deltaTime;
	//std::cout << FPS << std::endl;
	lastFrame = curFrame;
}

Game::Game(const char * name, int width, int hight)
	: m_width(width),m_hight(hight)
{
	

	/* Initialize the library */
	if (!glfwInit())
		return ;
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //OpenGL version 3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(m_width, m_hight, name, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return ;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
		std::cout << "error in glew" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	

	lastFrame = std::chrono::steady_clock::now();
	curScene = new Scene::GameScene(window);
	
}

Game::~Game()
{
	delete curScene;
	glfwTerminate();
}



void Game::GameLoop()
{
	UpdateDeltaBegain();
	
	curScene->Update(deltaTime);
	curScene->Render();
	curScene->GuiRender();
	

	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();
	UpdateDeltaEnd();
}

bool Game::IsRunning()
{
	return !glfwWindowShouldClose(window)&&!(glfwGetKey(window,GLFW_KEY_ESCAPE));
}


