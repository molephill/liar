#pragma once

namespace Liar
{
	// geometry类型
	enum GeometryType
	{
		GEOMETRY_NONE,
		GEOMETRY_TYPE_BOX
	};

	// geometry 里 vertex 类型
	enum GeometryVertexType
	{
		GEOMETRY_VERTEX_TYPE_NONE,
		GEOMETRY_VERTEX_TYPE_POSITION,
		GEOMETRY_VERTEX_TYPE_POSITION_NORMAL,
		GEOMETRY_VERTEX_TYPE_POSITION_COLOR,
		GEOMETRY_VERTEX_TYPE_POSITION_TEXTURE,
		GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR,
		GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE,
		GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR_TEXTURE,
		GEOMETRY_VERTEX_TYPE_POSITION_TEXTURE_SKIN,
		GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR_SKIN,
		GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE_SKIN,
		GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR_TEXTURE_SKIN
	};

	// 定义 vertex 类型占用 float 长度
	enum VertexElementFormatSize
	{
		ELEMENT_FORMAT_VECTOR2 = 2,
		ELEMENT_FORMAT_VECTOR3 = 3,
		ELEMENT_FORMAT_VECTOR4 = 4,
		ELEMENT_FORMAT_QUATERNION = 4,
		ELEMENT_FORMAT_UINT1 = 1,
		ELEMENT_FORMAT_UINT2 = 2,
		ELEMENT_FORMAT_UINT3 = 3,
		ELEMENT_FORMAT_UINT4 = 4
	};

	// 定义 vertex 类型属性
	enum VertexElementAttr
	{
		ELEMENT_ATTR_POSITION,
		ELEMENT_ATTR_NORMAL,
		ELEMENT_ATTR_TEXTURECOORDINATE,
		ELEMENT_ATTR_COLOR,
		ELEMENT_ATTR_ROTATION,
		ELEMENT_ATTR_RAW_KEY,
		ELEMENT_ATTR_RAW_INDICES,
		ELEMENT_ATTR_BONE_INDICES,
		ELEMENT_ATTR_BONE_WEIGHTS,
		ELEMENT_ATTR_SCALE
	};

	// 定义 vertex 类型占用的 bit
	enum VertexElementSize
	{
		ELEMENT_SIZE_VECTOR2 = 8,
		ELEMENT_SIZE_VECTOR3 = 12,
		ELEMENT_SIZE_VECTOR4 = 16,
		ELEMENT_SIZE_QUATERNION = 16,
		ELEMENT_SIZE_VECTOR3_DOUBLE = 24,
		ELEMENT_SIZE_INT = 4,
	};

	// 定义获取 vertex 类型
	enum VertexFormatType
	{
		VERTEX_FORMAT_TYPE_VECTOR2,
		VERTEX_FORMAT_TYPE_VECTOR3,
		VERTEX_FORMAT_TYPE_VECTOR4,
		VERTEX_FORMAT_TYPE_QUATERNION
	};

	// 定义数据索引
	enum VertexAttribPointer
	{
		ATTRIB_POINTER_POSITION,
		ATTRIB_POINTER_NORMAL,
		ATTRIB_POINTER_TEXTURECOORDINATE,
		ATTRIB_POINTER_COLOR,
		ATTRIB_POINTER_BONE_INDICES,
		ATTRIB_POINTER_BONE_WEIGHTS
	};
}