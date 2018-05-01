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
	Stone,
	BlockTypeCount
};

class Block
{
private:
	static	std::array<float, 120> vertix;
	static	std::array<unsigned int, 36> indecies;
	static	std::unique_ptr<VertexArray> va;
	static	std::unique_ptr<VertexBuffer> vb;
	static	std::unique_ptr<VertexBufferLayout> layout;
	static	std::unique_ptr<IndexBuffer> ib;

	std::unique_ptr<Texture> texture;
	bool Collide;
public:


	Block();
	Block(bool collide);
static  void		  Init();
		void		  SetTexture(const std::string& Path);
		void		  BindTexture(BlockType);
static	VertexArray*  GetVertexArray();
static	IndexBuffer*  GetIndexBuff();


};
