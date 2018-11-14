#pragma once

namespace Liar
{
	// mesh �� vertex ����
	enum MeshVertexType
	{
		POSITION = 0,
		POSITION_NORMAL,
		POSITION_NORMAL_COLOR,
		POSITION_NORMAL_TEXTURE,
		POSITION_NORMAL_COLOR_TEXTURE
	};

	// ���� vertex ����ռ�� float ����
	enum VertexElementFormat
	{
		VECTOR2 = 2,
		VECTOR3 = 3,
		VECTOR4 = 4,
		QUATERNION = 4
	};

	// ���� vertex ��������
	enum VertexElementAttr
	{
		POSITION = 0,
		NORMAL,
		TEXTURECOORDINATE,
		COLOR,
		ROTATION
	};

	// ���� vertex ����ռ�õ� bit
	enum VertexElementSize
	{
		VECTOR2 = 8,
		VECTOR3 = 12,
		VECTOR4 = 16,
		QUATERNION = 16,
		VECTOR3_DOUBLE = 24,
	};
}