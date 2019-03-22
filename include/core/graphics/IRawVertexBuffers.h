#pragma once

#include <core/graphics/VertexType.h>
#include <core/render/RenderState.h>
#include <LiarType.h>
#include <math/Vector3.h>
#include <math/Vector2.h>
#include <math/Quaternion.h>

namespace Liar
{
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

		Liar::IntHeapOperator** m_vertexKeys;
		Liar::Int m_numberVertexKeys;

		// �������
		Liar::Int m_mtlIndex;

		Liar::Int m_vertexIndex;

	protected:
		virtual size_t LoopUploadSubData(Liar::StageContext&, GLenum, Liar::Int, size_t) { return 0; };

		void AddRawKeyVertexBuffer(Liar::IntHeapOperator*);
		void SetRawKeyVertexBuffer(Liar::Int, Liar::IntHeapOperator*);
		void SetRawKeyVertexBufferLen(Liar::Int);
		void SetRawIndexLen(Liar::Int);

		void* GetRawKeyVertexBuffer(Liar::Int) const;
		void* GetRawIndex(Liar::Int) const;

	public:

		// ���� buffer ��Ϣ
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr, Liar::IHeapOperator*);
		virtual void SetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int index, Liar::IHeapOperator*);

		// ��֪ vertexBuffer ����
		virtual void SetSubVertexBufferLen(Liar::VertexElementAttr, Liar::Int);

		// ȡ�� buffer
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, Liar::Int);

		// ����ύָ������������Ϣ
		virtual void* GetUploadVertexBuffer(Liar::Int, Liar::VertexElementAttr) = 0;

		// ����������Ϣ
		void AddRawIndex(Liar::Int);
		void SetRawIndex(Liar::Int, Liar::Uint);

		Liar::Int GetNumberLength() const { return m_numberIndices; };

		// ��ò���������Ϣ
		Liar::Int GetMtlIndex() const { return m_mtlIndex; };
		void SetMtlIndex(Liar::Int index) { m_mtlIndex = index; };

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

		// ��
		virtual void VertexAttrbPointer() = 0;
	};
}