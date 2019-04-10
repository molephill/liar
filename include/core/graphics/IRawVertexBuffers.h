#pragma once

#include <core/graphics/VertexType.h>
#include <core/render/RenderState.h>
#include <core/render/TickRender.h>
#include <LiarType.h>
#include <math/Vector3.h>
#include <math/Vector2.h>
#include <math/Quaternion.h>
#include "ISubVertexBuffers.h"

namespace Liar
{
	/*
	* 顶点详细数据
	*/
	class IRawVertexBuffers:public Liar::ITickRender
	{
	public:
		IRawVertexBuffers(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~IRawVertexBuffers();

	protected:
		Liar::GeometryVertexType m_geomtryVertexType;

		Liar::Uint* m_indices;
		Liar::Int m_numberIndices;

		Liar::IntHeapOperator** m_vertexKeys;
		Liar::Int m_numberVertexKeys;

		// 共享材质
		Liar::Int m_mtlIndex;

		// current vertex index;
		Liar::Int m_vertexIndex;

		// current loop step;
		Liar::Int m_loopStep;
		Liar::Boolen m_uploaed;

	protected:
		virtual size_t VertexAttrbSubPointer(Liar::StageContext&, size_t) = 0;
		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t) { return 0; };

		void AddRawKeyVertexBuffer(Liar::IntHeapOperator*);
		void SetRawKeyVertexBuffer(Liar::Int, Liar::IntHeapOperator*);
		void SetRawKeyVertexBufferLen(Liar::Int);
		void SetRawIndexLen(Liar::Int);

		void* GetRawKeyVertexBuffer(Liar::Int) const;
		void* GetRawIndex(Liar::Int) const;

	public:
		// 设置 buffer 信息
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr, void*);
		virtual void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int index, void*);

		// 已知 vertexBuffer 长度
		virtual void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);

		// 取得 buffer
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int);

		// 获得提交指定顶点属性信息
		void* GetUploadVertexBuffer(Liar::Int, Liar::VertexElementAttr);

		// 顶点索引信息
		void AddRawIndex(Liar::Int);
		void SetRawIndex(Liar::Int, Liar::Uint);

		Liar::Int GetNumberLength() const { return m_numberIndices; };

		// 获得材质索引信息
		Liar::Int GetMtlIndex() const { return m_mtlIndex; };
		void SetMtlIndex(Liar::Int index) { m_mtlIndex = index; };

		// 获得三角形数据
		Liar::Int GetNumberTriangles() const { return m_numberIndices / 3; };

		// 获得顶点索引数据
		Liar::Uint* GetIndices() const { return m_indices; };

		// 是否已提交完
		Liar::Boolen GetUploaded() const { return m_uploaed; };

		// 获得步长
		virtual Liar::Int GetSize() const = 0;

		// 获得顶点数据总长度
		virtual Liar::Int GetBufferSize() const;

		// 提交数据
		virtual void UploadData(GLenum);

		// 打印
		virtual void Print(std::ostream&) const;

		// 分帧处理
		virtual bool TickRender(void* = nullptr, Liar::Int = Liar::TICK_INTERVAL);

	};
}