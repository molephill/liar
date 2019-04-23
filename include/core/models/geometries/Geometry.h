#pragma once

#include <core/resource/Resource.h>
#include <core/graphics/IRawVertexBuffers.h>
#include <core/graphics/VertexType.h>
#include <math/ByteArray.h>


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
		virtual bool RecreateSubResource() = 0;
		virtual Liar::Uint GetNumberLength() const;
		void UploadData();

	public:
		void SetGeometryVertexType(Liar::GeometryVertexType);
		Liar::IRawVertexBuffers* GetRawVertexBuffers() { return m_rawVertexBuffers; };
		Liar::GeometryVertexType GetGeoVertexType() const { return m_geometryVertexType; };
		Liar::Boolen GetUploaded() const { return m_rawVertexBuffers ? m_rawVertexBuffers->GetUploaded() : false; };
		virtual Liar::ClassType GetNodeType() const { return Liar::ClassType::CLASS_NODE_TYPE_GEOMETORY; };

	public:
		virtual void SetURL(const char*) {};
		virtual size_t GetNumberTriangles() const;
		virtual void Draws();
	};
}