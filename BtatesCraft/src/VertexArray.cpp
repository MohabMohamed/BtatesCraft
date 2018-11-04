#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "GLErrorHandler.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	
}


VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout)
{
	Bind();
	vb.Bind();
	const auto elements = layout.GetElements();
	GLchar* offset = 0;
	for (unsigned int i = 0; i<elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), offset);
		offset += element.count*VertexBufferElement::GetTypeSize(element.type);

	}

}

void VertexArray::AddBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout, const unsigned int instanceID, const VertexBufferLayout & instanceLayout)
{
	Bind();
	vb.Bind();
	const auto elements = layout.GetElements();
	const auto instanceElements = instanceLayout.GetElements();
	GLchar* offset = 0;
	unsigned int i;
	for (i = 0; i<elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)offset);
		offset += element.count*VertexBufferElement::GetTypeSize(element.type);

	}
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, instanceID));
	GLCall(glEnableVertexAttribArray(i));
	glVertexAttribPointer(i, instanceElements[0].count, instanceElements[0].type, instanceElements[0].normalized ? GL_TRUE : GL_FALSE, instanceLayout.GetStride(), (const void*)0);
	glVertexAttribDivisor(i, 1);
}


void VertexArray::AddBuffer(const VertexBuffer * vb, const VertexBufferLayout * layout, const unsigned int instanceID, const VertexBufferLayout * instanceLayout)
{
	Bind();
	vb->Bind();
	const auto elements = layout->GetElements();
	const auto instanceElements = instanceLayout->GetElements();
	GLchar* offset = 0;
	unsigned int i;
	for (i = 0; i<elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, layout->GetStride(), (const void*)offset);
		offset += element.count*VertexBufferElement::GetTypeSize(element.type);

	}
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, instanceID));
	GLCall(glEnableVertexAttribArray(i));
	glVertexAttribPointer(i, instanceElements[0].count, instanceElements[0].type, instanceElements[0].normalized ? GL_TRUE : GL_FALSE, instanceLayout->GetStride(), (const void*)0);
	glVertexAttribDivisor(i, 1);
}


void VertexArray::AddBuffer(const VertexBuffer && vb, const VertexBufferLayout && layout)
{
	Bind();
	vb.Bind();
	const auto elements = layout.GetElements();
	GLchar* offset = 0;
	for (unsigned int i=0;i<elements.size();i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		glVertexAttribPointer(i, element.count , element.type , element.normalized ? GL_TRUE:GL_FALSE, layout.GetStride(),(const void*) offset);
		offset += element.count*VertexBufferElement::GetTypeSize(element.type);

	}
	
}

void VertexArray::AddBuffer(const VertexBuffer && vb, const VertexBufferLayout && layout,const unsigned int instanceID, const VertexBufferLayout && instanceLayout)
{
	Bind();
	vb.Bind();
	const auto elements = layout.GetElements();
	const auto instanceElements = instanceLayout.GetElements();
	GLchar* offset = 0;
	unsigned int i;
	for (i = 0; i<elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)offset);
		offset += element.count*VertexBufferElement::GetTypeSize(element.type);

	}
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, instanceID));
	GLCall(glEnableVertexAttribArray(i));
	glVertexAttribPointer(i, instanceElements[0].count, instanceElements[0].type, instanceElements[0].normalized ? GL_TRUE : GL_FALSE, instanceLayout.GetStride(), (const void*)0);
	glVertexAttribDivisor(i, 1);
}



void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
