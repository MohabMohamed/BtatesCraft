#pragma once
#include <memory>
#include <array>
#include <chrono>
#include "glm/glm.hpp"

class BlockRenderManger;
class Camera;
class Chunck;
struct GLFWwindow;


#define		WORLD_LEN	10
#define		WORLD_AREA	WORLD_LEN*WORLD_LEN
class Game
{
private:
	int m_width,m_hight;
	GLFWwindow* window;
	std::chrono::steady_clock::time_point lastFrame;
	std::chrono::steady_clock::time_point curFrame;
	double deltaTime;
	double FPS;
	glm::mat4 ModelMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::mat4 MVP;
	unsigned int Seed;
	std::array<std::unique_ptr<Chunck>,WORLD_AREA > chuncks;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<BlockRenderManger> BlockRenderer;


private:
	inline void UpdateDeltaBegain();
	inline void UpdateDeltaEnd();
	void InitChunks();
public:
	
	Game(const char* name, int width,int hight);
	~Game();
void Init();
void GameLoop();
bool IsRunning();



};