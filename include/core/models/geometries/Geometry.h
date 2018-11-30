#pragma once

#include <core/resource/Resource.h>
#include <core/render/IRenderable.h>
#include <core/graphics/IVertexBuffer.h>
#include <core/graphics/raws/IRawVertexBuffers.h>


namespace Liar
{
	class Geometry :public Liar::Resource, public Liar::IRenderable
	{
	public:
		Geometry(GLenum type = GL_ARRAY_BUFFER);
		virtual ~Geometry();

	protected:
		Liar::GeometryVertexType m_geometryVertexType;

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
		virtual void RecreateResource();
		virtual void InitVertices(Liar::Uint) = 0;

	public:
		void SetGeometryVertexType(Liar::GeometryVertexType);

	public:
		virtual void GenAndBindVertex();
		virtual size_t GetRenderElementsCount();
		virtual const Liar::IRenderable* GetRenderElement(size_t) const;
		virtual void BeforeRender(Liar::RenderState&);
		virtual bool Render(Liar::StageContext& gl, Liar::RenderState& state);
		virtual size_t GetNumberTriangles();
		virtual Liar::IVertexBuffer* GetVertexBuff(size_t);
	};
}