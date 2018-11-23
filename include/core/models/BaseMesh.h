#pragma once

#include <core/resource/Resource.h>
#include <core/render/IRenderable.h>
#include <core/graphics/IVertexBuffer.h>
#include <core/graphics/raws/IRawVertexBuffers.h>


namespace Liar
{
	class BaseMesh :public Liar::Resource, public Liar::IRenderable
	{
	public:
		BaseMesh(GLenum type = GL_ARRAY_BUFFER);
		virtual ~BaseMesh();

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

	protected:
		virtual void DisposeResource();

	public:
		virtual void GenAndBindVertex();
		virtual size_t GetRenderElementsCount();
		virtual const Liar::IRenderable* GetRenderElement(size_t) const;
		virtual void BeforeRender(Liar::RenderState&);
	};
}