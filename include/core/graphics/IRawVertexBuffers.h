#pragma once

#include <core/graphics/VertexType.h>
#include <core/render/RenderState.h>
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

	protected:
		virtual void SetPositionIndex(Liar::Uint) = 0;
		virtual void SetNormalIndex(Liar::Uint) {};
		virtual void SetColorIndex(Liar::Uint) {};
		virtual void SetTexCoordIndex(Liar::Uint) {};

		virtual Liar::Uint GetPositionIndex() const  = 0;
		virtual Liar::Uint GetNormalIndex() const { return 0; };
		virtual Liar::Uint GetColorIndex() const { return 0; };
		virtual Liar::Uint GetTexCoordIndex() const { return 0; };

	public:
		void SetVertexIndex(Liar::VertexElementAttr, Liar::Uint);
		Liar::Uint GetVertexIndex(Liar::VertexElementAttr) const;
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

		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t) { return 0; };

		// 获得一个 raw_key 对象
		IVertexKey* CreateVertexKey(Liar::Number, Liar::Number, Liar::Number, Liar::Number);

		// 增加position信息
		virtual void AddPositionVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO) = 0;
		virtual void AddPositionVertexBuffer(const Liar::Vector3&) = 0;
		// 设置position信息
		virtual void SetPositionVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO) = 0;
		virtual void SetPositionVertexBuffer(size_t, Liar::Vector3*) =0;
		// 设置position长度
		virtual void SetPositionVertexBufferLen(Liar::Int) = 0;
		// 获得position信息
		virtual void* GetPostionVertexBuffer(size_t) const = 0;

		// 增加normal信息
		virtual void AddNormalVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO) {};
		virtual void AddNormalVertexBuffer(const Liar::Vector3&) {};
		// 设置normal信息
		virtual void SetNormalVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO) {};
		virtual void SetNormalVertexBuffer(size_t, Liar::Vector3*) {};
		// 设置normal长度
		virtual void SetNormalVertexBufferLen(Liar::Int) {};
		// 获得normal信息
		virtual void* GetNormalVertexBuffer(size_t) const { return nullptr; };

		// 增加color信息
		virtual void AddColorVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO) {};
		virtual void AddColorVertexBuffer(const Liar::Vector3&) {};
		// 设置color信息
		virtual void SetColorVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO) {};
		virtual void SetColorVertexBuffer(size_t, Liar::Vector3*) {};
		// 设置color长度
		virtual void SetColorVertexBufferLen(Liar::Int) {};
		// 获得color信息
		virtual void* GetColorVertexBuffer(size_t) const { return nullptr; };

		// 增加texcoord信息
		virtual void AddTexCoordVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO) {};
		virtual void AddTexCoordVertexBuffer(const Liar::Vector2&) {};
		// 设置texcoord信息
		virtual void SetTexCoordVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO) {};
		virtual void SetTexCoordVertexBuffer(size_t, Liar::Vector2*) {};
		// 设置texcoord长度
		virtual void SetTexCoordVertexBufferLen(Liar::Int) {};
		// 获得texcoord信息
		virtual void* GetTexCoordVertexBuffer(size_t) const { return nullptr; };

		// 增加rotation信息
		virtual void AddRotationVertexBuffer(Liar::Number, Liar::Number, Liar::Number, Liar::Number) {};
		virtual void AddRotationVertexBuffer(Liar::Vector4*) {};
		// 设置rotation信息
		virtual void SetRotationVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number, Liar::Number) {};
		virtual void SetRotationVertexBuffer(size_t, Liar::Vector4*) {};
		// 设置rotation长度
		virtual void SetRotationVertexBufferLen(Liar::Int) {};
		// 获得rotation信息
		virtual void* GetRotationVertexBuffer(size_t) const { return nullptr; };

		// 增加raw_key信息
		virtual void AddRawKeyVertexBuffer(Liar::Number, Liar::Number, Liar::Number, Liar::Number);
		virtual void AddRawKeyVertexBuffer(Liar::IVertexKey*);
		// 设置raw_key信息
		virtual void SetRawKeyVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number, Liar::Number);
		virtual void SetRawKeyVertexBuffer(size_t, Liar::IVertexKey*);
		// 设置raw_key长度
		virtual void SetRawKeyVertexBufferLen(Liar::Int);
		// 获得raw_key信息
		virtual void* GetRawKeyVertexBuffer(Liar::Int) const;

		// 增加raw_index信息
		virtual void AddRawIndex(Liar::Int);
		// 设置raw_index信息
		virtual void SetRawIndex(size_t, Liar::Number);
		// 设置raw_index长度
		virtual void SetRawIndexLen(Liar::Int);
		// 获得raw_index信息
		virtual void* GetRawIndex(size_t) const;

	public:
		void AddSubVertexBuffer(Liar::VertexElementAttr, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO);
		void* GetSubVertexBuffer(Liar::VertexElementAttr, size_t);

		// 已知 vertexBuffer 长度
		void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);
		void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO);

		Liar::Int GetNumberLength() const { return m_numberIndices; };

		// 获得材质索引信息
		Liar::Int GetMtlIndex() const { return m_mtlIndex; };
		void SetMtlIndex(Liar::Int index) { m_mtlIndex = index; };

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