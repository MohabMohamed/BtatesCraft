#include "BlockDataBase.h"

void BlockDataBase::Init()
{

	__Blocks[(int8_t) BlockType::Air] = std::make_unique<Block>(false);
	__Blocks[(int8_t)BlockType::Grass] = std::make_unique<Block>();
	__Blocks[(int8_t)BlockType::Dirt] = std::make_unique<Block>();
	__Blocks[(int8_t)BlockType::Stone] = std::make_unique<Block>();
	__Blocks[(int8_t)BlockType::Grass]->SetTexture("res/Textures/Grass.png");
	//TODO : set the rest textures


}

const Block & BlockDataBase::GetBlockData(BlockType type) 
{
	return __Blocks[(int8_t)type].get();
}
