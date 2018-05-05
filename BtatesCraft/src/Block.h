#pragma once
#include <memory>
#include <array>
#include <string>
#include "VertexBufferLayout.h"
#include "BlockType.h"
#include "Texture.h"

class VertexBuffer;
class IndexBuffer;


class Block
{
private:
	static	std::array<float, 120> vertix;
	static	std::array<unsigned int, 36> indecies;

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
static	VertexBuffer*  GetVertexBuffer();
static	VertexBufferLayout*  GetVertexLayout();
static	IndexBuffer*  GetIndexBuff();


};
