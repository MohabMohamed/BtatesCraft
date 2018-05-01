#pragma once
#include "Block.h"

namespace BlockDataBase
{

std::array<std::unique_ptr<Block>,(int8_t) BlockType::BlockTypeCount> __Blocks;

void	Init();
const Block&  GetBlockData(BlockType type );


};
