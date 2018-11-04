#include "Chunck.h"
#include <algorithm>
#include "BlockType.h"
#include "BlockRenderManger.h"
#include "vendor/PerlinNoise/PerlinNoise.h"

Chunck::Chunck(BlockRenderManger * blocksRenderer, const glm::ivec2& position, unsigned int seed)
	:Position(position),BlocksRenderer(blocksRenderer)
{

	PerlinNoise noise(seed);
	
	glm::vec2 normPos;
	normPos.x = float(position.x) / 5.0f;
	normPos.y = float(position.y) / 5.0f;
	double xnor, znor,hight;
	for(int x=0;x<16;x++)
	{
		 xnor = double(x) / 40;
		 for (int z = 0; z < 16; z++)
		{
			 znor = double(z) / 40;
			hight =std::ceil(map(noise.noise(xnor + normPos.x/10, 0.5, znor + normPos.y/10),0,1.0,4.0,16.0));
	
			
			for (int y = 0; y < 16; y++)
			{
				if (y == 0)Blocks[x][y][z] = (int8_t)BlockType::Stone;
				else if (y > hight)Blocks[x][y][z] = (int8_t)BlockType::Air;
				else Blocks[x][y][z] = (int8_t) map(noise.noise(xnor + normPos.x,  normPos.y, znor + double(z) / 40),0,1.0,1.0,(double)BlockType::BlockTypeCount);
				if (y < hight&&Blocks[x][y][z] == (int8_t)BlockType::Grass)Blocks[x][y][z] = (int8_t)BlockType::Dirt;
				if (y == hight&&Blocks[x][y][z] == (int8_t)BlockType::Dirt)Blocks[x][y][z] = (int8_t)BlockType::Grass;
				blocksRenderer->AddBlock(BlockType(Blocks[x][y][z]), position, x, y, z);
			}

		}
	}

}

Chunck::~Chunck()
{
    BlocksRenderer->DeleteChunk(Position);
}

int8_t Chunck::GetType(int x, int y, int z)
{
	return Blocks[x][y][z];
}

glm::ivec2 Chunck::GetPosition()
{
	return Position;
}


int Chunck::NumDigits(int number)
{
	int digits = 0;
	if (number < 0) digits = 1; 
	while (number) {
		number /= 10;
		digits++;
	}
	return digits;
}


