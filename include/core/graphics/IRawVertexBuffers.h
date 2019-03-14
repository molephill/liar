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
	* ��������
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
	* ������ϸ����
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

		// �������
		Liar::Int m_mtlIndex;

		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t) { return 0; };

		// ���һ�� raw_key ����
		IVertexKey* CreateVertexKey(Liar::Number, Liar::Number, Liar::Number, Liar::Number);

		// ����position��Ϣ
		virtual void AddPositionVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO) = 0;
		virtual void AddPositionVertexBuffer(const Liar::Vector3&) = 0;
		// ����position��Ϣ
		virtual void SetPositionVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO) = 0;
		virtual void SetPositionVertexBuffer(size_t, Liar::Vector3*) =0;
		// ����position����
		virtual void SetPositionVertexBufferLen(Liar::Int) = 0;
		// ���position��Ϣ
		virtual void* GetPostionVertexBuffer(size_t) const = 0;

		// ����normal��Ϣ
		virtual void AddNormalVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO) {};
		virtual void AddNormalVertexBuffer(const Liar::Vector3&) {};
		// ����normal��Ϣ
		virtual void SetNormalVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO) {};
		virtual void SetNormalVertexBuffer(size_t, Liar::Vector3*) {};
		// ����normal����
		virtual void SetNormalVertexBufferLen(Liar::Int) {};
		// ���normal��Ϣ
		virtual void* GetNormalVertexBuffer(size_t) const { return nullptr; };

		// ����color��Ϣ
		virtual void AddColorVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO) {};
		virtual void AddColorVertexBuffer(const Liar::Vector3&) {};
		// ����color��Ϣ
		virtual void SetColorVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO) {};
		virtual void SetColorVertexBuffer(size_t, Liar::Vector3*) {};
		// ����color����
		virtual void SetColorVertexBufferLen(Liar::Int) {};
		// ���color��Ϣ
		virtual void* GetColorVertexBuffer(size_t) const { return nullptr; };

		// ����texcoord��Ϣ
		virtual void AddTexCoordVertexBuffer(Liar::Number, Liar::Number, Liar::Number = Liar::ZERO) {};
		virtual void AddTexCoordVertexBuffer(const Liar::Vector2&) {};
		// ����texcoord��Ϣ
		virtual void SetTexCoordVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO) {};
		virtual void SetTexCoordVertexBuffer(size_t, Liar::Vector2*) {};
		// ����texcoord����
		virtual void SetTexCoordVertexBufferLen(Liar::Int) {};
		// ���texcoord��Ϣ
		virtual void* GetTexCoordVertexBuffer(size_t) const { return nullptr; };

		// ����rotation��Ϣ
		virtual void AddRotationVertexBuffer(Liar::Number, Liar::Number, Liar::Number, Liar::Number) {};
		virtual void AddRotationVertexBuffer(Liar::Vector4*) {};
		// ����rotation��Ϣ
		virtual void SetRotationVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number, Liar::Number) {};
		virtual void SetRotationVertexBuffer(size_t, Liar::Vector4*) {};
		// ����rotation����
		virtual void SetRotationVertexBufferLen(Liar::Int) {};
		// ���rotation��Ϣ
		virtual void* GetRotationVertexBuffer(size_t) const { return nullptr; };

		// ����raw_key��Ϣ
		virtual void AddRawKeyVertexBuffer(Liar::Number, Liar::Number, Liar::Number, Liar::Number);
		virtual void AddRawKeyVertexBuffer(Liar::IVertexKey*);
		// ����raw_key��Ϣ
		virtual void SetRawKeyVertexBuffer(size_t, Liar::Number, Liar::Number, Liar::Number, Liar::Number);
		virtual void SetRawKeyVertexBuffer(size_t, Liar::IVertexKey*);
		// ����raw_key����
		virtual void SetRawKeyVertexBufferLen(Liar::Int);
		// ���raw_key��Ϣ
		virtual void* GetRawKeyVertexBuffer(Liar::Int) const;

		// ����raw_index��Ϣ
		virtual void AddRawIndex(Liar::Int);
		// ����raw_index��Ϣ
		virtual void SetRawIndex(size_t, Liar::Number);
		// ����raw_index����
		virtual void SetRawIndexLen(Liar::Int);
		// ���raw_index��Ϣ
		virtual void* GetRawIndex(size_t) const;

	public:
		void AddSubVertexBuffer(Liar::VertexElementAttr, Liar::Number, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO);
		void* GetSubVertexBuffer(Liar::VertexElementAttr, size_t);

		// ��֪ vertexBuffer ����
		void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);
		void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int, Liar::Number, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO, Liar::Number = Liar::ZERO);

		Liar::Int GetNumberLength() const { return m_numberIndices; };

		// ��ò���������Ϣ
		Liar::Int GetMtlIndex() const { return m_mtlIndex; };
		void SetMtlIndex(Liar::Int index) { m_mtlIndex = index; };

		// ��Ⲣ�Ƿ����Ӷ�����������
		virtual void CheckAddVertexKey(const Liar::IVertexKey&);

		// �������������
		Liar::Int GetNumberTriangles() const { return m_numberIndices / 3; };

		// ��ö�����������
		Liar::Uint* GetIndices() { return m_indices; };

		// ��ò���
		virtual Liar::Int GetStride() const = 0;

		// ��ö��������ܳ���
		virtual Liar::Int GetBufferSize() const;

		// �ύ����
		virtual void UploadData(GLenum);

		// ����ύָ������������Ϣ
		virtual void* GetUploadVertexBuffer(Liar::Int, Liar::VertexElementAttr);

		// ��
		virtual void VertexAttrbPointer() = 0;

		// ��ӡ����
		virtual void PrintData() = 0;
	};
}