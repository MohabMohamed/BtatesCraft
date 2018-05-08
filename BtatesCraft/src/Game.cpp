#include "Game.h"
#include <iostream>
#include "gl/glew.h"
#include "gl/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "Camera.h"
#include "BlockRenderManger.h"
#include "Chunck.h"
#include "Block.h"



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
	std::cout << FPS << std::endl;
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
	Seed = std::chrono::steady_clock::now().time_since_epoch().count();
	Init();
	
}

Game::~Game()
{
		glfwTerminate();
}

void Game::Init()
{
	BlockRenderer = std::make_unique<BlockRenderManger>();
	camera = std::make_unique<Camera>(window);
	ModelMatrix = glm::translate(0, 0, 0);
	ViewMatrix = camera->GetViewMat();
	ProjectionMatrix = glm::perspective(
		45.0f, 4.0f / 3.0f, 1.0f, 1000.0f);
	MVP = ProjectionMatrix*ViewMatrix*ModelMatrix;

	BlockRenderer = std::make_unique<BlockRenderManger>();
	lastFrame = std::chrono::steady_clock::now();
	glm::ivec2 pos;
	for (int i = 0; i < WORLD_AREA; i++) 
	{
		pos.x = i / WORLD_LEN;
		pos.y = i % WORLD_LEN;
			chuncks[i] = std::make_unique<Chunck>(BlockRenderer.get(), pos*16 , Seed);
		
	}
}

void Game::GameLoop()
{
	UpdateDeltaBegain();
	BlockRenderer->Clear();

	camera->Input(deltaTime);
	ViewMatrix = camera->GetViewMat();

	MVP = ProjectionMatrix*ViewMatrix*ModelMatrix;

	BlockRenderer->SetMVP(MVP);
	BlockRenderer->Render();

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


