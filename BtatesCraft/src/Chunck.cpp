#include "Chunck.h"
#include <algorithm>
#include "BlockType.h"
#include "BlockRenderManger.h"
#include "vendor/PerlinNoise/PerlinNoise.h"

Chunck::Chunck(BlockRenderManger * blocksRenderer,glm::ivec2& position, unsigned int seed)
	:Position(position),BlocksRenderer(blocksRenderer)
{

	PerlinNoise noise(seed);
	
	int normlizer = std::pow(10, std::max(NumDigits(position.x), NumDigits(position.y)));
	glm::vec2 normPos;
	normPos.x = float(position.x) / float(normlizer);
	normPos.y = float(position.y) / float(normlizer);
	double xnor, ynor,hight;
	for(int x=0;x<16;x++)
	{
		 xnor = double(x) / 16;
		for (int y = 0; y < 16; y++) 
		{
			 ynor = double(y) / 16;
			hight =std::ceil(map(noise.noise(xnor + normPos.x, ynor + normPos.y, 0.5),0,1.0,4.0,16.0));
	
			for (int z = 0; z < 16; z++)
			{
				if (z == 0)Blocks[x][y][z] = (int8_t)BlockType::Stone;
				else if (z > hight)Blocks[x][y][z] = (int8_t)BlockType::Air;
				else Blocks[x][y][z] = (int8_t) map(noise.noise(xnor + normPos.x, ynor + normPos.y, double(z) / 16),0,1.0,1.0,(double)BlockType::BlockTypeCount-1);
				blocksRenderer->AddBlock(BlockType(Blocks[x][y][z]), position, x, y, z);
			}

		}
	}

}

Chunck::~Chunck()
{
	for (int x = 0; x < 16; x++)
	{

		for (int y = 0; y < 16; y++)
		{

			for (int z = 0; z < 16; z++)
			{
				BlocksRenderer->DeleteBlock(BlockType(Blocks[x][y][z]), Position, x, y, z);
			}
		}
	}
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


