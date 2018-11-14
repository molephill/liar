#pragma once

namespace Liar
{
	// mesh 里 vertex 类型
	enum MeshVertexType
	{
		POSITION = 0,
		POSITION_NORMAL,
		POSITION_NORMAL_COLOR,
		POSITION_NORMAL_TEXTURE,
		POSITION_NORMAL_COLOR_TEXTURE
	};

	// 定义 vertex 类型占用 float 长度
	enum VertexElementFormat
	{
		VECTOR2 = 2,
		VECTOR3 = 3,
		VECTOR4 = 4,
		QUATERNION = 4
	};

	// 定义 vertex 类型属性
	enum VertexElementAttr
	{
		POSITION = 0,
		NORMAL,
		TEXTURECOORDINATE,
		COLOR,
		ROTATION
	};

	// 定义 vertex 类型占用的 bit
	enum VertexElementSize
	{
		VECTOR2 = 8,
		VECTOR3 = 12,
		VECTOR4 = 16,
		QUATERNION = 16,
		VECTOR3_DOUBLE = 24,
	};
}