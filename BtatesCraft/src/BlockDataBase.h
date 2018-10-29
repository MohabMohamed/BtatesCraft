#pragma once
#include "BlockType.h"
#include <array>
#include <memory>

class Block;
class VertexBuffer;
class IndexBuffer;
class VertexBufferLayout;

namespace BlockDataBase
{



void	Init();
 Block&  GetBlockData(BlockType type );
VertexBuffer*  GetVertexBuffer();
VertexBufferLayout*  GetVertexLayout();
IndexBuffer*  GetIndexBuff();

}
