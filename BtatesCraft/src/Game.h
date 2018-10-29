#pragma once
#include <chrono>
#include <memory>

struct GLFWwindow;
namespace Scene
{
	class Scene;
}

class Game
{
private:
	int m_width,m_hight;
	GLFWwindow* window;
	Scene::Scene* curScene;
	std::chrono::steady_clock::time_point lastFrame;
	std::chrono::steady_clock::time_point curFrame;
	double deltaTime;
	double FPS;

public:
	
	Game(const char* name, int width,int hight);
	~Game();
void GameLoop();
bool IsRunning();

private:
	inline void UpdateDeltaBegain();
	inline void UpdateDeltaEnd();



};
