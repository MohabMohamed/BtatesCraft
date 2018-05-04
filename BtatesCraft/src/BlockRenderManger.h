#pragma once
#include <vector>
#include <array>
#include <glm\glm.hpp>
#include "BlockType.h"


class  BlockRenderManger
{
private:
	
	std::array<std::vector<glm::ivec3>, int8_t(BlockType::BlockTypeCount) - 1 > m_RenderBlocks;
	std::array<unsigned int, int8_t(BlockType::BlockTypeCount) - 1> m_typeInstanceID;
public:
	 BlockRenderManger();
	~BlockRenderManger();
	void AddBlock(BlockType type,glm::ivec2 ChunkOffset,int x, int y, int z);
	void DeleteBlock(BlockType type, glm::ivec2 ChunkOffset, int x, int y, int z);
private:
	void UpdateBlocks(BlockType type);

};


