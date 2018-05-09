#include "BlockRenderManger.h"
#include "glm\gtc\type_ptr.hpp"
#include "BlockDataBase.h"
#include "Block.h"



BlockRenderManger::BlockRenderManger()
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

void BlockRenderManger::DeleteBlock(BlockType type, glm::ivec2 ChunkOffset, int x, int y, int z)
{
	if (type == BlockType::Air)
		return;

	int fullX = ChunkOffset.x + x;
	int fullz = ChunkOffset.y + z;
	
	for (auto it = m_RenderBlocks[(int)type-1].begin(); it != m_RenderBlocks[(int)type - 1].end(); ++it)
	{
		if(it->x==fullX && it->y == y && it->z == fullz)
		{
			m_RenderBlocks[(int)type - 1].erase(it);
			break;
		}
	}
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
	int x=5;
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
