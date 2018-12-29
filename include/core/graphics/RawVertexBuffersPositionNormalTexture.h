#pragma once

#include <core/graphics/IRawVertexBuffers.h>
#include <math/Vector3.h>
#include <math/Vector2.h>

namespace Liar
{
	class VertexPositionNormalTextureKey :public Liar::IVertexKey
	{
	public:
		VertexPositionNormalTextureKey();
		virtual ~VertexPositionNormalTextureKey() {};

	private:
		Liar::Uint m_positonIndex;
		Liar::Uint m_normalIndex;
		Liar::Uint m_texCoordIndex;

	public:
		virtual void SetVertexIndex(Liar::VertexElementAttr, Liar::Uint);
		virtual Liar::Uint GetVertexIndex(Liar::VertexElementAttr) const;
		virtual void PrintData();
		virtual Liar::Boolen operator==(const Liar::IVertexKey&) const;
		virtual Liar::IVertexKey* Clone() const;
	};

	class RawVertexBuffersPositionNormalTexture :public Liar::IRawVertexBuffers
	{
	public:
		RawVertexBuffersPositionNormalTexture(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositionNormalTexture();

	private:
		Liar::Vector3** m_positons;
		Liar::Uint m_numberPostions;

		Liar::Vector3** m_normals;
		Liar::Uint m_numberNormals;

		Liar::Vector2** m_texCoords;
		Liar::Uint m_numberTexCoodrs;

	protected:
		virtual void AddPositonVertex(Liar::Number x, Liar::Number y, Liar::Number z);
		virtual void AddNormalVertex(Liar::Number x, Liar::Number y, Liar::Number z);
		virtual void AddTexCoordVertex(Liar::Number x, Liar::Number y);
		virtual void UploadSubData(GLenum);

	public:
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number);
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, size_t);

		virtual void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);
		virtual void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int, Liar::Number, Liar::Number, Liar::Number = 0.0f, Liar::Number = 0.0f);

		virtual Liar::Int GetStride() const;
		virtual void VertexAttrbPointer();

		virtual void PrintData();
	};
}