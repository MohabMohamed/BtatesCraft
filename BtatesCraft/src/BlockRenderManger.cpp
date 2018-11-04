#include "BlockRenderManger.h"
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>
#include "BlockDataBase.h"
#include "Block.h"



BlockRenderManger::BlockRenderManger()
    : firstTime(true)
{
	m_instancingLayout = std::make_unique<VertexBufferLayout>();
	m_instancingLayout->Push<int>(3);

	Block::Init();

	for (int i = 0; i < int(BlockType::BlockTypeCount) - 1; i++)
	{
		GLCall(glGenBuffers(1, &m_typeInstanceID[i]));
		m_va[i] = std::make_unique<VertexArray>();

	}
	renderer = std::make_unique<Renderer>();
	blockShader = std::make_unique<Shader>("res/Shaders/Block.shader");
	BlockDataBase::Init();

	//loop for each type and do this line
	for (int i = 0; i <int( BlockType::BlockTypeCount) - 1; i++){
		m_va[(int)i ]->AddBuffer(BlockDataBase::GetVertexBuffer(), BlockDataBase::GetVertexLayout(), m_typeInstanceID[(int)i ], m_instancingLayout.get());
}}

BlockRenderManger::~BlockRenderManger()
{
	for (int i = 0; i < int(BlockType::BlockTypeCount) - 1; i++)
	{
		GLCall(glDeleteBuffers(1, &m_typeInstanceID[i]));
	
	}
}

void BlockRenderManger::AddBlock(BlockType type, glm::ivec2 ChunkOffset, int x, int y, int z)
{
	if (type == BlockType::Air)
		return;
	m_RenderBlocks[(int)type - 1].push_back(glm::ivec3(ChunkOffset.x + x, y, ChunkOffset.y + z) );
	//UpdateBlocks(type);
	firstTime = true;
}

void BlockRenderManger::DeleteChunk(glm::ivec2 ChunkOffset)
{
    for (auto& blocks : m_RenderBlocks)
    {
        std::remove_if(blocks.begin(),
                     blocks.end(),
                     [&](auto&& block)
                     {
                         return (block.x >= ChunkOffset.x
                                 && block.x < ChunkOffset.x + 16
                                 && block.y >= ChunkOffset.y
                                 && block.y < ChunkOffset.y + 16);
                     });
    }
}

void BlockRenderManger::DeleteBlock(BlockType type, glm::ivec2 ChunkOffset, int x, int y, int z)
{
	if (type == BlockType::Air)
		return;

	int fullX = ChunkOffset.x + x;
	int fullz = ChunkOffset.y + z;

    auto& blocks = m_RenderBlocks[(int)type-1];
    auto it = std::find_if(blocks.begin(),
                           blocks.end(),
                           [&](auto&& block)
                           {
                               return (block.x == fullX
                                       && block.y == y
                                       && block.z == fullz);
                           });
    if (it != blocks.end()) blocks.erase(it);
//	UpdateBlocks(type);
	firstTime = true;
}

void BlockRenderManger::Clear()
{
	renderer->Clear();
}

void BlockRenderManger::Render()
{
	for (int i = 0; i<int(BlockType::BlockTypeCount) - 1; i++)
	{
		if(firstTime)
			UpdateBlocks(BlockType(i+1));
		blockShader->Bind();
		blockShader->SetUniformElement("MVP", MVP);
		BlockDataBase::GetBlockData(BlockType(i + 1)).BindTexture();
		renderer->Draw(*m_va[i], *BlockDataBase::GetIndexBuff(), *blockShader,m_RenderBlocks[i].size());
	
	}
	firstTime = false;
}

void BlockRenderManger::SetMVP(glm::mat4& mvp)
{
	MVP = mvp;

}

void BlockRenderManger::UpdateBlocks(BlockType type)
{
	m_va[(int)type - 1]->Bind();
	
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_typeInstanceID[(int)type - 1]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_RenderBlocks[(int)type - 1].size() * sizeof(glm::ivec3), glm::value_ptr(m_RenderBlocks[(int)type - 1][0]), GL_DYNAMIC_DRAW));


	
}
