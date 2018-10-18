#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLErrorHandler.h>


struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;
	static unsigned int GetTypeSize(unsigned int type) 
	{
		switch (type)
		{
		case GL_UNSIGNED_BYTE:
			return 1;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_FLOAT:
			return 4;
		case GL_INT:
			return 4;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_stride;
public:
	VertexBufferLayout():m_stride(0)
	{
	
	}
	~VertexBufferLayout() {}

	template <typename T>
	void Push(unsigned count) {
        static_assert("Push needs to be overridden for the typename T provided");
	}

	inline unsigned int GetStride() const { return m_stride; }
	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; } //should add &
};
