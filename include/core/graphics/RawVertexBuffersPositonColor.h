#pragma once

#include "RawVertexBuffersPosition.h"

namespace Liar
{
	class VertexPositionColorKey :public Liar::VertexPositionKey
	{
	public:
		VertexPositionColorKey();
		virtual ~VertexPositionColorKey() {};

	protected:
		Liar::Uint m_colorIndex;
		virtual void SetColorIndex(Liar::Uint val) { m_colorIndex = val; };
		virtual Liar::Uint GetColorIndex() const { return m_colorIndex; };

	public:
		virtual void PrintData();
		virtual Liar::Boolen operator==(const Liar::IVertexKey&) const;
		virtual Liar::IVertexKey* Clone() const;
	};

	class RawVertexBuffersPositonColor:public RawVertexBuffersPosition
	{
	public:
		RawVertexBuffersPositonColor(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPositonColor();

	protected:
		Liar::SubVector3VertexBuffer* m_color;

	protected:
		// ����color��Ϣ
		virtual void AddColorVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO);
		virtual void AddColorVertexBuffer(const Liar::Vector3&);
		// ����color��Ϣ
		virtual void SetColorVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO);
		virtual void SetColorVertexBuffer(size_t, Liar::Vector3*);
		// ����color����
		virtual void SetColorVertexBufferLen(Liar::Int);
		// ���color��Ϣ
		virtual void* GetColorVertexBuffer(size_t) const;

		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t);
		virtual size_t VertexAttrbSubPointer(Liar::StageContext&, size_t);

	public:
		virtual Liar::Int GetStride() const;
	};
}