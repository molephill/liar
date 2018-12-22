#pragma once

#include <core/graphics/VertexType.h>
#include <LiarType.h>
#include <math/Vector3.h>
#include <math/Vector2.h>
#include <math/Quaternion.h>

namespace Liar
{
	static const char* VERTEX_ATTRIB_POSITION0 = "POSITION0";
	static const char* VERTEX_ATTRIB_NORMAL0 = "NORMAL0";
	static const char* VERTEX_ATTRIB_TEXCOORDINATE0 = "TEXCOORDNIATE0";

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
		IRawVertexBuffers(Liar::Boolen createTmp = true);
		virtual ~IRawVertexBuffers();

	protected:
		Liar::Uint* m_indices;
		Liar::Int m_numberIndices;

		Liar::IVertexKey** m_vertexKeys;
		Liar::Int m_numberVertexKeys;

		// ����������ʱ����
		Liar::IVertexKey* m_tmpKey;
		Liar::Uint m_tmpIndex;

		void* GetVertexBuffer(Liar::VertexElementAttr, void**, size_t, Liar::Number, Liar::Number, Liar::Number z = 0.0f, Liar::Number w = 0.0f);
		virtual void UploadSubData(GLenum) = 0;

	public:
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr, Liar::Number, Liar::Number, Liar::Number = 0.0f, Liar::Number = 0.0f) = 0;
		virtual void* GetSubVertexBuffer(Liar::VertexElementAttr, size_t) = 0;

		// ���ö�������
		virtual void SetIndicesLength(Liar::Int);
		virtual void SetIndex(Liar::Int, Liar::Uint);
		Liar::Int GetNumberLength() const { return m_numberIndices; };

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

		// ����
		virtual std::string GetAttribDefines() = 0;

		// ��ӡ����
		virtual void PrintData() = 0;
	};
}