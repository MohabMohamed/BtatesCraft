#pragma once
#include <vector>
#include <array>
#include <memory>
#include "glm\glm.hpp"
#include "BlockType.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"


class  BlockRenderManger
{
private:
	
	std::array<std::vector<glm::ivec3>, int(BlockType::BlockTypeCount) - 1 > m_RenderBlocks;
	std::array<unsigned int, int(BlockType::BlockTypeCount) - 1> m_typeInstanceID;
	std::array<std::unique_ptr<VertexArray>, int(BlockType::BlockTypeCount) - 1> m_va;
	std::unique_ptr<VertexBufferLayout> m_instancingLayout;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Shader> blockShader;
	glm::mat4 MVP;
	bool firstTime = true;
public:
	 BlockRenderManger();
	~BlockRenderManger();
	void AddBlock(BlockType type,glm::ivec2 ChunkOffset,int x, int y, int z);
	void DeleteBlock(BlockType type, glm::ivec2 ChunkOffset, int x, int y, int z);
	void Clear();
	void Render();
	void SetMVP(glm::mat4& mvp);
private:
	void UpdateBlocks(BlockType type);

};


