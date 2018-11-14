#pragma once

#include <core/resource/Resource.h>
#include <core/graphics/IVertexBuffer.h>
#include <core/graphics/raws/IRawVertexBuffers.h>
#include <core/render/IRenderable.h>
#include <algorithm>

namespace Liar
{
	class BaseMesh :public Liar::Resource, public Liar::IRenderable
	{
	public:
		BaseMesh(GLenum type = GL_ARRAY_BUFFER) :
			Liar::Resource(),
			Liar::IRenderable(),
			m_bufferSubType(type),
			m_rawVertexBuffers(nullptr),
			m_vertexArray(0), m_vertexBuffer(0), m_elementBuffer(0),
			m_vertices(nullptr), m_numberVertices(0),
			m_indices(nullptr), m_numberIndices(0)
		{};
		virtual ~BaseMesh()
		{
		};

	protected:
		GLenum m_bufferSubType;
		Liar::IRawVertexBuffers* m_rawVertexBuffers;

		Liar::IVertexBuffer** m_vertices;
		Liar::Uint m_numberVertices;

		Liar::Uint* m_indices;
		Liar::Uint m_numberIndices;

		Liar::Uint m_vertexArray;
		Liar::Uint m_vertexBuffer;
		Liar::Uint m_elementBuffer;

	public:
		virtual void DisposeResource()
		{
			if (m_vertexArray > 0) Liar::GL::mainContext.DeleteBuffers(1, &m_vertexArray);
			if (m_vertexBuffer > 0) Liar::GL::mainContext.DeleteBuffers(1, &m_vertexBuffer);
			if (m_elementBuffer > 0) Liar::GL::mainContext.DeleteBuffers(1, &m_elementBuffer);

			for (size_t i = 0; i < m_numberVertices; ++i)
			{
				m_vertices[i]->~IVertexBuffer();
				m_vertices[i] = nullptr;
			}
			if (m_vertices) free(m_vertices);
			m_vertices = nullptr;

			if (m_rawVertexBuffers)
			{
				m_rawVertexBuffers->~IRawVertexBuffers();
				free(m_rawVertexBuffers);
				m_rawVertexBuffers = nullptr;
			}

			if (m_indices) free(m_indices);
			m_indices = nullptr;

			Liar::Resource::Destroy();
		}

		virtual void GenAndBindVertex()
		{
			Liar::GLContext& gl = Liar::GL::mainContext;
			gl.GenVertexArrays(1, &m_vertexArray);
			gl.BindVertexArray(m_vertexArray);

			gl.GenBuffers(1, &m_vertexBuffer);
			gl.BindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

			// indices data
			size_t indicesSize = m_numberIndices * sizeof(Liar::Uint);
			gl.GenBuffers(1, &m_elementBuffer);
			gl.BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
			gl.BufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, m_indices, GL_STATIC_DRAW);

			// vertex data
			size_t i = 0;
			size_t stride = m_vertices[i]->GetStride();
			size_t bufferSize = m_numberVertices * stride;
			gl.BufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);

			for (i = 0; i < m_numberVertices; ++i)
			{
				size_t start = i * stride;
				m_vertices[i]->BufferSubData(m_bufferSubType, start);
			}
		};

		virtual size_t GetRenderElementsCount()
		{
			return 1;
		};

		virtual const Liar::IRenderable* GetRenderElement(size_t) const
		{
			return this;
		}

		virtual void BeforeRender(Liar::RenderState&)
		{
			Liar::GL::mainContext.BindVertexArray(m_vertexArray);
		}
	};
}