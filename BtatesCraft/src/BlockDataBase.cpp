#include "BlockDataBase.h"
#include "Block.h"

namespace BlockDataBase {
	std::array<std::unique_ptr<Block>, (int)BlockType::BlockTypeCount> __Blocks;
}
void BlockDataBase::Init()
{

	__Blocks[(int8_t) BlockType::Air] = std::make_unique<Block>(false);
	__Blocks[(int8_t)BlockType::Grass] = std::make_unique<Block>();
	__Blocks[(int8_t)BlockType::Dirt] = std::make_unique<Block>();
	__Blocks[(int8_t)BlockType::Stone] = std::make_unique<Block>();
	__Blocks[(int8_t)BlockType::Grass]->SetTexture("res/Textures/Grass.png");
	__Blocks[(int8_t)BlockType::Dirt]->SetTexture("res/Textures/Dirt.png");
	__Blocks[(int8_t)BlockType::Stone]->SetTexture("res/Textures/Sand.png");

}

 Block & BlockDataBase::GetBlockData(BlockType type) 
{
	return *__Blocks[(int8_t)type];
}

 VertexBuffer * BlockDataBase::GetVertexBuffer()
 {
	 return Block::GetVertexBuffer();
 }

 VertexBufferLayout * BlockDataBase::GetVertexLayout()
 {
	 return Block::GetVertexLayout();
 }

 IndexBuffer * BlockDataBase::GetIndexBuff()
 {
	 return Block::GetIndexBuff();
 }
