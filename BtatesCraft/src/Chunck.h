#pragma once
#include <cstdint>
#include "glm/glm.hpp"

class BlockRenderManger;

class  Chunck
{
private:
	int8_t Blocks[16][16][16];
	glm::ivec2 Position;
	BlockRenderManger * BlocksRenderer;
public:
	Chunck(BlockRenderManger * blocksRenderer,glm::ivec2& position, unsigned int seed);
	~Chunck();
	int8_t GetType(int x, int y, int z);
	glm::ivec2 GetPosition();

private:
	int NumDigits(int number);
	inline double map(double value, double minInRange, double maxInRange, double minOutRange, double maxOutRange)
	{
	return  minOutRange + (maxOutRange - minOutRange) * (value / (maxInRange - minInRange)); 
	}
};

