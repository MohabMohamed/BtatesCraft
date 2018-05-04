#include "BlockRenderManger.h"
#include "GLErrorHandler.h"
#include <glm\gtc\type_ptr.hpp>
#include <GL\glew.h>

BlockRenderManger::BlockRenderManger()
{
	for (int i = 0; i < int(BlockType::BlockTypeCount) - 1; i++)
	{
		glGenBuffers(1, &m_typeInstanceID[i]);
	}

}

BlockRenderManger::~BlockRenderManger()
{
}

void BlockRenderManger::AddBlock(BlockType type, glm::ivec2 ChunkOffset, int x, int y, int z)
{
	m_RenderBlocks[(int)type - 1].push_back(glm::ivec3(ChunkOffset.x + x, ChunkOffset.y + y, z) );
	UpdateBlocks(type);

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
	UpdateBlocks(type);
}

void BlockRenderManger::UpdateBlocks(BlockType type)
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_typeInstanceID[(int)type - 1]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_RenderBlocks[(int)type - 1].size() * sizeof(glm::ivec3), glm::value_ptr(m_RenderBlocks[(int)type - 1][0]), GL_STATIC_DRAW));
}
