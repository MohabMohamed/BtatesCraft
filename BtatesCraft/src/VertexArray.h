#pragma once
#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();
	void AddBuffer(const VertexBuffer&, const VertexBufferLayout&);
	void AddBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout, const unsigned int instanceID, const VertexBufferLayout & instanceLayout);
	void AddBuffer(const VertexBuffer * vb, const VertexBufferLayout * layout, const unsigned int instanceID, const VertexBufferLayout * instanceLayout);
	void AddBuffer(const VertexBuffer&&,const VertexBufferLayout&&);
	void AddBuffer(const VertexBuffer && vb, const VertexBufferLayout && layout, const unsigned int instanceID, const VertexBufferLayout && instanceLayout);

	void Bind() const;
	void Unbind() const;
};

