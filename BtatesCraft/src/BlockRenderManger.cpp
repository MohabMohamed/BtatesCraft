#include "BlockRenderManger.h"
#include <glm\gtc\type_ptr.hpp>
#include "BlockDataBase.h"
#include "Block.h"

BlockRenderManger::BlockRenderManger()
{
	m_instancingLayout = std::make_unique<VertexBufferLayout>();
	m_instancingLayout->Push<int>(3);
	for (int i = 0; i < int(BlockType::BlockTypeCount) - 1; i++)
	{
		GLCall( glGenBuffers(1, &m_typeInstanceID[i]));
		m_va[i] = std::make_unique<VertexArray>();
		m_va[i]->AddBuffer(*BlockDataBase::GetVertexBuffer(), *BlockDataBase::GetVertexLayout(), m_typeInstanceID[i], *m_instancingLayout);
	}
	renderer = std::make_unique<Renderer>();
	blockShader = std::make_unique<Shader>("res/Shaders/Block.shader"); 
	BlockDataBase::Init();
}

BlockRenderManger::~BlockRenderManger()
{
	for (int i = 0; i < int(BlockType::BlockTypeCount) - 1; i++)
	{
		GLCall(glDeleteBuffers(1, &m_typeInstanceID[i]));
	
	}
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

void BlockRenderManger::Render()
{
	
	for (int i = 0; i<int(BlockType::BlockTypeCount) - 1; i++)
	{
		blockShader->Bind();
		BlockDataBase::GetBlockData(BlockType(i + 1)).BindTexture(BlockType(i + 1));
		renderer->Draw(*m_va[i], *BlockDataBase::GetIndexBuff(), *blockShader,m_RenderBlocks[i].size());
	
	}
}

void BlockRenderManger::UpdateBlocks(BlockType type)
{
	m_va[(int)type - 1]->Bind();
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_typeInstanceID[(int)type - 1]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_RenderBlocks[(int)type - 1].size() * sizeof(glm::ivec3), glm::value_ptr(m_RenderBlocks[(int)type - 1][0]), GL_STATIC_DRAW));
	

	
}
