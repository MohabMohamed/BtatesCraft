#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLErrorHandler.h>
#include <assert.h>

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
	template <typename... T>
	struct wrong_param
	{
		static constexpr bool value = false;
	};
public:
	VertexBufferLayout():m_stride(0)
	{
	
	}
	~VertexBufferLayout() {}

	inline unsigned int GetStride() const { return m_stride; }
	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; } //should add &
	
	template <typename T>
	void Push(unsigned count) {
		static_assert(wrong_param<T>::value, "Push needs to be overridden for the typename T provided");
	}

	template <>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT,count,false });
		m_stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
	}

	template <>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,false });
		m_stride += count *  VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT);
	}
	template <>
	void Push<int>(unsigned int count)
	{
		m_Elements.push_back({ GL_INT,count,false });
		m_stride += count *  VertexBufferElement::GetTypeSize(GL_INT);
	}

	template <>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,true });
		m_stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE);
	}



};
