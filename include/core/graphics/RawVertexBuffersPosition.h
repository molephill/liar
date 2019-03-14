#pragma once

#include "IRawVertexBuffers.h"
#include "SubVertexBuffers.h"

#include <core/render/RenderState.h>
#include <math/Vector3.h>

namespace Liar
{
	class VertexPositionKey :public Liar::IVertexKey
	{
	public:
		VertexPositionKey();
		virtual ~VertexPositionKey() {};

	protected:
		Liar::Uint m_positonIndex;
		virtual void SetPositionIndex(Liar::Uint val) { m_positonIndex = val; };
		virtual Liar::Uint GetPositionIndex() const { return m_positonIndex; };

	public:
		virtual void PrintData();
		virtual Liar::Boolen operator==(const Liar::IVertexKey&) const;
		virtual Liar::IVertexKey* Clone() const;
	};

	class RawVertexBuffersPosition :public Liar::IRawVertexBuffers
	{
	public:
		RawVertexBuffersPosition(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~RawVertexBuffersPosition();

	protected:
		Liar::SubVector3VertexBuffer* m_position;

	protected:
		// 增加position信息
		virtual void AddPositionVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO);
		virtual void AddPositionVertexBuffer(const Liar::Vector3&);
		// 设置position信息
		virtual void SetPositionVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO);
		virtual void SetPositionVertexBuffer(size_t, Liar::Vector3*);
		// 设置position长度
		virtual void SetPositionVertexBufferLen(Liar::Int);
		// 获得position信息
		virtual void* GetPostionVertexBuffer(size_t) const;

		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t);
		virtual size_t VertexAttrbSubPointer(Liar::StageContext&, size_t);

	public:
		virtual Liar::Int GetStride() const;
		virtual void VertexAttrbPointer();

		virtual void PrintData();
	};
}
