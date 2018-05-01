#pragma once
#include <memory>
#include <array>
#include <string>
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

enum class BlockType 
{
	Air,
	Grass,
	Dirt,
	Water,
	BlockTypeCount
};

class Block
{
private:
	std::array<float, 120> vertix;
	std::array<unsigned int, 36> indecies;
	std::unique_ptr<VertexArray> va;
	std::unique_ptr<VertexBuffer> vb;
	std::unique_ptr<VertexBufferLayout> layout;
	std::unique_ptr<IndexBuffer> ib;
	std::unique_ptr<Texture> texture;
	bool Collide;
public:
	Block();
	void		  SetTexture(std::string& Path);
	void		  BindTexture(BlockType);
	VertexArray*  GetVertexArray();
	IndexBuffer*  GetIndexBuff();


};
