#include "Game.h"

using namespace std::chrono_literals;

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
	Init();
}

Game::~Game()
{
	shader.~unique_ptr();
	tex.~unique_ptr();
	ib.~unique_ptr();
	vb.~unique_ptr();
	va.~unique_ptr();
	
	glfwTerminate();
}

void Game::Init()
{
	vertix = {
		//cube clock wise
		//front 
		1.0f, 1.0f,0.0f, 0.25f,0.0f,
		1.0f,0.0f,0.0f,  0.5f,0.0f,
		0.0f,0.0f,0.0f,   0.5f,1.0f,
		0.0f,1.0f,0.0f,  0.25f,1.0f,
		//back
		1.0f, 1.0f,1.0f, 0.25f,0.0f,
		1.0f,0.0f,1.0f,  0.5f,0.0f,
		0.0f,0.0f,1.0f,   0.5f,1.0f,
		0.0f,1.0f,1.0f,  0.25f,1.0f,
	

	};
	
	indecies =
	{
		//front
		0,1,2,
		2,3,0,
		//back
		4,5,6,
		6,7,4,
		//right
		4,5,1,
		1,0,4,
		//left
		3,2,6,
		6,7,3,
		//up
		4,0,3,
		3,7,4,
		//down
		5,1,2,
		2,6,5
	};
	va = std::make_unique<VertexArray>();
	vb = std::make_unique<VertexBuffer>(vertix.data(), vertix.size() * sizeof(float));
	layout = std::make_unique<VertexBufferLayout>();
	layout->Push<float>(3);
	layout->Push<float>(2);
	va->AddBuffer(*vb, *layout);
	ib = std::make_unique<IndexBuffer>(indecies.data(), 36);
	shader = std::make_unique<Shader>("res/Shaders/Basic.shader");

	//glm::mat4 translateMat = glm::translate(0.5f, -0.5f, 0.0f);
	//glm::mat4 scaleMat = glm::scale(0.3f, 0.3f, 0.0f);

	//ModelMatrix = translateMat* scaleMat;
	ViewMatrix = glm::lookAt(
		glm::vec3(0.0f, 0.5f, 3),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0, 1, 0)
	);
	ProjectionMatrix = glm::perspective(
		45.0f, 4.0f / 3.0f, 1.0f, 100.0f);
	MVP = ProjectionMatrix*ViewMatrix*ModelMatrix;

	tex = std::make_unique<Texture>("res/Textures/Grass.png");

	tex->Bind();
	shader->Bind();
	shader->SetUniformElement("MVP", MVP);
	shader->Unbind();

	renderer = std::make_unique<Renderer>();
	lastFrame = std::chrono::steady_clock::now();
}

void Game::GameLoop()
{
	UpdateDeltaBegain();
	renderer->Clear();


	va->Bind();
	ib->Bind();

	shader->Bind();

	shader->SetUniformElement("MVP", MVP);
	shader->SetUniformElement("u_texture", 0);
	shader->SetUniformElement("color", 0.5f, 0.2f, 0.1f, 1.0f);

	renderer->Draw(*va,* ib, *shader);

	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();
	UpdateDeltaEnd();
}

bool Game::IsRunning()
{
	return !glfwWindowShouldClose(window);
}


