#pragma once
#include "BlockDataBase.h"
#include <glm\glm.hpp>

class  BlockRenderManger
{
private:
	
	std::array<std::vector<glm::ivec3>, int8_t(BlockType::BlockTypeCount) - 1 > m_RenderBlocks;

public:
	 BlockRenderManger();
	~BlockRenderManger();
	void AddBlock(BlockType type,glm::ivec2 ChunkOffset,int x, int y, int z);
	void DeleteBlock(BlockType type, glm::ivec2 ChunkOffset, int x, int y, int z);


};


