#include "Block.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"



std::array<float, 120> Block::vertix;
std::array<unsigned int, 36> Block::indecies;
std::unique_ptr<VertexBuffer> Block::vb;
std::unique_ptr<VertexBufferLayout> Block::layout;
std::unique_ptr<IndexBuffer> Block::ib;


Block::Block()
	:Collide(true)
{}

Block::Block(bool collide)
	:Collide(collide)
{}

void Block::Init()
{
	vertix = {
		//cube clock wise
		//front 
		1.0f, 1.0f,0.0f, 0.25f,0.0f,
		1.0f,0.0f,0.0f,  0.5f,0.0f,
		0.0f,0.0f,0.0f,   0.5f,1.0f,
		0.0f,1.0f,0.0f,  0.25f,1.0f,
		//back
		1.0f, 1.0f,1.0f, 0.25f,0.0f,
		1.0f,0.0f,1.0f,  0.5f,0.0f,
		0.0f,0.0f,1.0f,   0.5f,1.0f,
		0.0f,1.0f,1.0f,  0.25f,1.0f,
		//up
		1.0f, 1.0f,1.0f, 0.0f,0.0f,
		1.0f, 1.0f,0.0f, 0.25f,0.0f,
		0.0f,1.0f,0.0f,  0.25f,1.0f,
		0.0f,1.0f,1.0f,  0.0f,1.0f,
		//Right
		1.0f, 1.0f,1.0f, 0.25f,0.0f,
		1.0f,0.0f,1.0f,  0.5f,0.0f,
		1.0f,0.0f,0.0f,  0.5f,1.0f,
		1.0f, 1.0f,0.0f, 0.25f,1.0f,
		//left
		0.0f,1.0f,1.0f,  0.25f,0.0f,
		0.0f,1.0f,0.0f,  0.25f,1.0f,
		0.0f,0.0f,0.0f,   0.5f,1.0f,
		0.0f,0.0f,1.0f,  0.5f,0.0f,
		//down
		1.0f,0.0f,1.0f,  0.75f,0.0f,
		0.0f,0.0f,1.0f,   0.75f,1.0f,
		0.0f,0.0f,0.0f,   0.5f,1.0f,
		1.0f,0.0f,0.0f,  0.5f,0.0f
	};

	indecies =
	{
		//front
		0,1,2,
		2,3,0,
		//back
		4,5,6,
		6,7,4,
		//up
		8,9,10,
		10,11,8,
		//right
		12,13,14,
		14,15,12,
		//left
		16,17,18,
		18,19,16,

		//down
		20,21,22,
		22,23,20
	};
	
	vb = std::make_unique<VertexBuffer>(vertix.data(), vertix.size() * sizeof(float));
	layout = std::make_unique<VertexBufferLayout>();
	layout->Push<float>(3);
	layout->Push<float>(2);
	
	ib = std::make_unique<IndexBuffer>(indecies.data(), 36);
}

void Block::SetTexture(const std::string& Path)
{
	texture = std::make_unique<Texture>(Path);
}

void Block::BindTexture(BlockType Type)
{
	texture->Bind(unsigned int(Type) - 1);
}

VertexBuffer * Block::GetVertexBuffer()
{
	return vb.get();
}

VertexBufferLayout * Block::GetVertexLayout()
{
	return layout.get();
}


IndexBuffer* Block::GetIndexBuff()
{
	return ib.get();
}
