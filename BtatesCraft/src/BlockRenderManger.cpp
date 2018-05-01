#include "BlockRenderManger.h"


BlockRenderManger::BlockRenderManger()
{

}

BlockRenderManger::~BlockRenderManger()
{
}

void BlockRenderManger::AddBlock(BlockType type, glm::ivec2 ChunkOffset, int x, int y, int z)
{
	m_RenderBlocks[(int)type - 1].push_back(glm::ivec3(ChunkOffset.x + x, ChunkOffset.y + y, z) );
}

void BlockRenderManger::DeleteBlock(BlockType type, glm::ivec2 ChunkOffset, int x, int y, int z)
{
	if (type == BlockType::Air)
		return;

	int fullX = ChunkOffset.x + x;
	int fullY = ChunkOffset.y + y;
	
	for (auto it = m_RenderBlocks[(int)type-1].begin(); it != m_RenderBlocks[(int)type - 1].end(); ++it)
	{
		if(it->x==fullX && it->y == fullY && it->z == z)
		{
			m_RenderBlocks[(int)type - 1].erase(it);
			break;
		}
	}
}
