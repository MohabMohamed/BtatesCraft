#include "VertexBufferLayout.h"

template <>
void VertexBufferLayout::Push<float>(unsigned int count) 
{
    m_Elements.push_back({ GL_FLOAT,count,false });
    m_stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
}

template <>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    m_Elements.push_back({ GL_UNSIGNED_INT,count,false });
    m_stride += count *  VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT);
}
template <>
void VertexBufferLayout::Push<int>(unsigned int count)
{
    m_Elements.push_back({ GL_INT,count,false });
    m_stride += count *  VertexBufferElement::GetTypeSize(GL_INT);
}

template <>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    m_Elements.push_back({ GL_UNSIGNED_BYTE,count,true });
    m_stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE);
}
