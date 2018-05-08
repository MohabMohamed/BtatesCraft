#include "Game.h"
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
	/*vertix = {
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
		//up
		1.0f, 1.0f,1.0f, 0.0f,0.0f,
		1.0f, 1.0f,0.0f, 0.25f,0.0f,
		0.0f,1.0f,0.0f,  0.25f,1.0f,
		0.0f,1.0f,1.0f,  0.0f,1.0f,
		//Right
		1.0f, 1.0f,1.0f, 0.25f,0.0f,
		1.0f,0.0f,1.0f,  0.5f,0.0f,
		1.0f,0.0f,0.0f,  0.5f,1.0f,
		1.0f, 1.0f,0.0f, 0.25f,1.0f,
		//left
		0.0f,1.0f,1.0f,  0.25f,0.0f,
		0.0f,1.0f,0.0f,  0.25f,1.0f,
		0.0f,0.0f,0.0f,   0.5f,1.0f,
		0.0f,0.0f,1.0f,  0.5f,0.0f,
		//down
		1.0f,0.0f,1.0f,  0.75f,0.0f,
		0.0f,0.0f,1.0f,   0.75f,1.0f,
		0.0f,0.0f,0.0f,   0.5f,1.0f,
		1.0f,0.0f,0.0f,  0.5f,0.0f
	};
	
	indecies =
	{
		//front
		0,1,2,
		2,3,0,
		//back
		4,5,6,
		6,7,4,
		//up
		8,9,10,
		10,11,8,
		//right
		12,13,14,
		14,15,12,
		//left
		16,17,18,
		18,19,16,
		
		//down
		20,21,22,
		22,23,20
	};
	va = std::make_unique<VertexArray>();
	vb = std::make_unique<VertexBuffer>(vertix.data(), vertix.size() * sizeof(float));
	layout = std::make_unique<VertexBufferLayout>();
	layout->Push<float>(3);
	layout->Push<float>(2);
	va->AddBuffer(*vb, *layout);
	ib = std::make_unique<IndexBuffer>(indecies.data(), 36);
	shader = std::make_unique<Shader>("res/Shaders/Basic.shader");

	tex = std::make_unique<Texture>("res/Textures/Grass.png");

	tex->Bind();
	shader->Bind();
	shader->SetUniformElement("MVP", MVP);
	shader->Unbind();

	*/
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
	for (int i = 0; i < CHUNCK_VOL; i++) 
	{
		pos.x = i / CHUNCK_DIM;
		pos.y = i % CHUNCK_DIM;
			chuncks[i] = std::make_unique<Chunck>(BlockRenderer.get(), pos*16 , Seed);
		
	}
}

void Game::GameLoop()
{
	UpdateDeltaBegain();
	renderer->Clear();

	camera->Input(deltaTime);
	/*va->Bind();
	ib->Bind();

	shader->Bind();

	shader->SetUniformElement("MVP", MVP);
	shader->SetUniformElement("u_texture", 0);
	shader->SetUniformElement("color", 0.5f, 0.2f, 0.1f, 1.0f);

	renderer->Draw(*va,* ib, *shader);*/

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


