#pragma once
#include "BlockType.h"
#include <array>
#include <memory>

class Block;


namespace BlockDataBase
{

std::array<std::unique_ptr<Block>,(int8_t) BlockType::BlockTypeCount> __Blocks;

void	Init();
const Block&  GetBlockData(BlockType type );


};
