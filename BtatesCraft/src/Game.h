#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <array>
#include <chrono>
#include <thread>
#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Camera.h"
#include "Renderer.h"
#include "BlockRenderManger.h"


class Game
{
private:
	int m_width,m_hight;
	GLFWwindow* window;
	std::unique_ptr<Renderer> renderer;
	std::chrono::steady_clock::time_point lastFrame;
	std::chrono::steady_clock::time_point curFrame;
	double deltaTime;
	double FPS;
	glm::mat4 ModelMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::mat4 MVP;
	unsigned int MatID;

	std::unique_ptr<Camera> camera;
	std::unique_ptr<Shader> BlockShader;
	std::unique_ptr<BlockRenderManger> BlockRenderer;
	//delete below(just for testing)
	/*
	
	std::unique_ptr<Texture> tex;
	std::array<float,120> vertix;
	std::array<unsigned int,36> indecies;
	std::unique_ptr<VertexArray> va;
	std::unique_ptr<VertexBuffer> vb;
	std::unique_ptr<VertexBufferLayout> layout;
	std::unique_ptr<IndexBuffer> ib;*/

private:
	inline void UpdateDeltaBegain();
	inline void UpdateDeltaEnd();
public:
	
	Game(const char* name, int width,int hight);
	~Game();
void Init();
void GameLoop();
bool IsRunning();



};