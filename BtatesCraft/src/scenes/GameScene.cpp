#include "GameScene.h"
#include <chrono>
#include "irrKlang/irrKlang.h"
#include "gl/glew.h"
#include "gl/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "Camera.h"
#include "BlockRenderManger.h"
#include "Chunck.h"
#include "Block.h"
#include "BlockPicker.h"




Scene::GameScene::GameScene(GLFWwindow* window)
{
	Seed = std::chrono::steady_clock::now().time_since_epoch().count();

	BlockRenderer = std::make_unique<BlockRenderManger>();
	camera = std::make_unique<Camera>(window);
	ModelMatrix = glm::translate(0, 0, 0);
	ViewMatrix = camera->GetViewMat();
	ProjectionMatrix = glm::perspective(
		45.0f, 4.0f / 3.0f, 1.0f, 1000.0f);
	MVP = ProjectionMatrix*ViewMatrix*ModelMatrix;

	BlockRenderer = std::make_unique<BlockRenderManger>();
	Picker = std::make_unique<BlockPicker>(window, camera.get(), ProjectionMatrix);
	
	InitChunks();

	SoundEngine = irrklang::createIrrKlangDevice();
	if (!SoundEngine)
		return;

	SoundEngine->play2D("res/sounds/cave story theme piano.mp3", true);
}

Scene::GameScene::~GameScene()
{
	SoundEngine->drop();
}

void Scene::GameScene::Update(double deltaTime)
{
	camera->Input(deltaTime);
	ViewMatrix = camera->GetViewMat();

	MVP = ProjectionMatrix*ViewMatrix*ModelMatrix;

	BlockRenderer->SetMVP(MVP);
}

void Scene::GameScene::Render()
{
	BlockRenderer->Clear();

	BlockRenderer->Render();
}

void Scene::GameScene::GuiRender()
{
}

void Scene::GameScene::InitChunks()
{
	glm::ivec2 pos;
	int i = 0;
	for (int x = WORLD_LEN / 2 * -1; x < WORLD_LEN / 2; x++)
	{
		for (int y = WORLD_LEN / 2 * -1; y < WORLD_LEN / 2; y++) {
			pos.x = x;
			pos.y = y;
			chuncks[i] = std::make_unique<Chunck>(BlockRenderer.get(), pos * 16, Seed);
			i++;
		}
	}
}
