#pragma once

#include <core/graphics/VertexType.h>
#include <LiarType.h>
#include <math/Vector3.h>
#include <math/Vector2.h>
#include <math/Quaternion.h>

namespace Liar
{
	/**
	* 顶点索引
	*/
	class IVertexKey
	{
	public:
		IVertexKey() {};
		virtual ~IVertexKey() {};

	public:
		virtual void SetVertexIndex(Liar::VertexElementAttr, Liar::Uint) = 0;
		virtual Liar::Uint GetVertexIndex(Liar::VertexElementAttr) const = 0;
		virtual void PrintData() = 0;
		virtual Liar::Boolen operator==(const Liar::IVertexKey&) const = 0;
		virtual Liar::IVertexKey* Clone() const = 0;
	};

	/*
	* 顶点详细数据
	*/
	class IRawVertexBuffers
	{
	public:
		IRawVertexBuffers(Liar::GeometryVertexType type = Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_NONE);
		virtual ~IRawVertexBuffers();

	protected:
		Liar::GeometryVertexType m_geomtryVertexType;

		Liar::Uint* m_indices;
		Liar::Int m_numberIndices;

		Liar::IVertexKey** m_vertexKeys;
		Liar::Int m_numberVertexKeys;

		// 共享材质
		Liar::Int m_mtlIndex;

		void* GetVertexBuffer(Liar::VertexElementAttr, void**, size_t, Liar::Number, Liar::Number, Liar::Number z = 0.0f, Liar::Number w = 0.0f);
		virtual void UploadSubData(GLenum) = 0;

		// 不知长度时推入
		void PushIndices(Liar::Uint);
		void PushVertexKey(Liar::IVertexKey*);

	public:
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr, Liar::Number, Liar::Number, Liar::Number = 0.0f, Liar::Number = 0.0f) = 0;
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, size_t) = 0;

		// 已知 vertexBuffer 长度
		virtual void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);
		virtual void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int, Liar::Number, Liar::Number = 0.0f, Liar::Number = 0.0f, Liar::Number = 0.0f);

		// 设置顶点索引
		virtual void SetIndicesLength(Liar::Int);
		virtual void SetIndex(Liar::Int, Liar::Uint);
		Liar::Int GetNumberLength() const { return m_numberIndices; };

		// 获得材质索引信息
		Liar::Int GetMtlIndex() const { return m_mtlIndex; };
		void SetMtlIndex(Liar::Int index) { m_mtlIndex = index; };

		// 设置顶点数据索引
		virtual void SetVertexKeyLength(Liar::Int);
		virtual void SetVertexKey(Liar::Int, Liar::IVertexKey*);

		// 检测并是否增加顶点索引数据
		virtual void CheckAddVertexKey(const Liar::IVertexKey&);

		// 获得三角形数据
		Liar::Int GetNumberTriangles() const { return m_numberIndices / 3; };

		// 获得顶点索引数据
		Liar::Uint* GetIndices() { return m_indices; };

		// 获得步长
		virtual Liar::Int GetStride() const = 0;

		// 获得顶点数据总长度
		virtual Liar::Int GetBufferSize() const;

		// 提交数据
		virtual void UploadData(GLenum);

		// 获得提交指定顶点属性信息
		virtual void* GetUploadVertexBuffer(Liar::Int, Liar::VertexElementAttr);

		// 绑定
		virtual void VertexAttrbPointer() = 0;

		// 打印数据
		virtual void PrintData() = 0;
	};
}