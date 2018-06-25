#pragma once
#include "Scene.h"
#include <memory>
#include <array>
#include "glm/glm.hpp"





class BlockRenderManger;
class Camera;
class Chunck;
class BlockPicker;
struct GLFWwindow;
namespace irrklang {
	class ISoundEngine;
};

namespace Scene 
{


#define		WORLD_LEN	10
#define		WORLD_AREA	WORLD_LEN*WORLD_LEN


	class GameScene: public Scene
	{
	private:
		irrklang::ISoundEngine* SoundEngine;
		glm::mat4 ModelMatrix;
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionMatrix;
		glm::mat4 MVP;
		unsigned int Seed;
		std::array<std::unique_ptr<Chunck>, WORLD_AREA > chuncks;
		std::unique_ptr<Camera> camera;
		std::unique_ptr<BlockPicker> Picker;
		std::unique_ptr<BlockRenderManger> BlockRenderer;
	public:
		GameScene(GLFWwindow* window);
		~GameScene();
		void Update(double deltaTime) override;
		void Render() override;
		void GuiRender() override;
	private:
		void InitChunks();
	

	};

	


};