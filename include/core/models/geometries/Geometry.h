#pragma once

#include <core/resource/Resource.h>
#include <core/graphics/IRawVertexBuffers.h>
#include <core/graphics/VertexType.h>


namespace Liar
{
	class Geometry :public Liar::Resource
	{
	public:
		Geometry(Liar::GeometryVertexType geometryType = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE, 
			GLenum type = GL_ARRAY_BUFFER);
		virtual ~Geometry();

	protected:
		Liar::GeometryVertexType m_geometryVertexType;

		GLenum m_bufferSubType;
		Liar::IRawVertexBuffers* m_rawVertexBuffers;

		Liar::Uint m_vertexArray;
		Liar::Uint m_vertexBuffer;
		Liar::Uint m_elementBuffer;

	protected:
		virtual void DisposeResource();
		virtual void RecreateResource();
		virtual void VertexAttrbPointer() = 0;
		virtual void RecreateSubResource() = 0;
		virtual IVertexKey* PopVertexKey();
		void UploadData();

	public:
		void SetGeometryVertexType(Liar::GeometryVertexType);

	public:
		virtual size_t GetNumberTriangles();
		virtual std::string GetAttribDefines();
		virtual void Draws();
	};
}