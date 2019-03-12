#pragma once

#include <core/graphics/VertexType.h>
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

	public:
		virtual void SetVertexIndex(Liar::VertexElementAttr, Liar::Uint) = 0;
		virtual Liar::Uint GetVertexIndex(Liar::VertexElementAttr) const = 0;
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

		void* GetVertexBuffer(Liar::VertexElementAttr, void**, size_t, Liar::Number, Liar::Number, Liar::Number z = 0.0f, Liar::Number w = 0.0f);
		virtual void UploadSubData(GLenum) = 0;

		// ��֪����ʱ����
		void PushIndices(Liar::Uint);
		void PushVertexKey(Liar::IVertexKey*);

	public:
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr, Liar::Number, Liar::Number, Liar::Number = 0.0f, Liar::Number = 0.0f) = 0;
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, size_t) = 0;

		// ��֪ vertexBuffer ����
		virtual void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);
		virtual void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int, Liar::Number, Liar::Number = 0.0f, Liar::Number = 0.0f, Liar::Number = 0.0f);

		// ���ö�������
		virtual void SetIndicesLength(Liar::Int);
		virtual void SetIndex(Liar::Int, Liar::Uint);
		Liar::Int GetNumberLength() const { return m_numberIndices; };

		// ��ò���������Ϣ
		Liar::Int GetMtlIndex() const { return m_mtlIndex; };
		void SetMtlIndex(Liar::Int index) { m_mtlIndex = index; };

		// ���ö�����������
		virtual void SetVertexKeyLength(Liar::Int);
		virtual void SetVertexKey(Liar::Int, Liar::IVertexKey*);

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