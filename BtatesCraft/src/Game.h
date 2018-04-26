#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <array>
#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

class Game
{
private:
	int m_width,m_hight;
	GLFWwindow* window;
	std::unique_ptr<Renderer> renderer;
	glm::mat4 ModelMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::mat4 MVP;
	unsigned int MatID;
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Texture> tex;
	//delete below(just for testing)
	std::array<float,20> vertix;
	std::array<unsigned int,6> indecies;
	std::unique_ptr<VertexArray> va;
	std::unique_ptr<VertexBuffer> vb;
	std::unique_ptr<VertexBufferLayout> layout;
	std::unique_ptr<IndexBuffer> ib;

public:
	
	Game(const char* name, int width,int hight);
	~Game();
void Init();
void GameLoop();
bool IsRunning();


};