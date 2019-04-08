
#include <core/models/geometries/NetGeometry.h>
#include <Liar3D.h>

namespace Liar
{
	NetGeometry::NetGeometry():
		Liar::Geometry()
	{
	}

	NetGeometry::~NetGeometry()
	{
	}

	Liar::Boolen NetGeometry::operator==(const char* url) const
	{
		return strcmp(url, m_url.c_str()) == 0;
	}

	Liar::Boolen NetGeometry::operator==(const Liar::NetGeometry& source) const
	{
		return source.m_url == m_url;
	}

	void NetGeometry::SetURL(const char* url)
	{
		if (m_url != url)
		{
			m_url = url;
			DisposeResource();
			RecreateResource();
		}
	}

	void NetGeometry::RecreateSubResource()
	{
		std::string realPath = Liar::Liar3D::urlFormat->FormatSourceURL(m_url.c_str());

		FILE* pFile = nullptr;
#ifndef __APPLE__
		fopen_s(&pFile, realPath.c_str(), "rb+");
#else
		pFile = fopen(path, "rb+");
#endif
		// geometry类型
		Liar::Int type = 0;
		fread(&type, sizeof(Liar::Int), 1, pFile);
		m_geometryVertexType = static_cast<Liar::GeometryVertexType>(type);
		m_rawVertexBuffers = Liar::Liar3D::geometryFactory->GetVertexFactory().GetRawVertexBuffers(m_geometryVertexType);
		// 顶点类型
		ReadDynamicVertex(m_geometryVertexType, pFile);
		ReadTypeVertex(pFile);			// keys
		ReadTypeVertex(pFile);			// indices
		// 引用材质索引
		Liar::Int mtlIndex = 0;
		fread(&mtlIndex, sizeof(Liar::Int), 1, pFile);
		m_rawVertexBuffers->SetMtlIndex(mtlIndex);

		fclose(pFile);

		std::ofstream out("C:/Users/Administrator/Desktop/model/out1.txt");
		m_rawVertexBuffers->Print(out);
		out.close();
	}

	void NetGeometry::ReadDynamicVertex(Liar::GeometryVertexType type, FILE* pFile)
	{
		switch (type)
		{
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL:
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_COLOR:
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_TEXTURE:
			LoopReadTypeVertex(pFile);
			break;
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR:
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_TEXTURE_SKIN:
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE:
			LoopReadTypeVertex(pFile, 3);
			break;
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR_TEXTURE:
			LoopReadTypeVertex(pFile, 4);
			break;
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR_SKIN:
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE_SKIN:
			LoopReadTypeVertex(pFile, 5);
			break;
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR_TEXTURE_SKIN:
			LoopReadTypeVertex(pFile, 6);
			break;
		default:
			break;
		}
	}

	void NetGeometry::LoopReadTypeVertex(FILE* pFile, Liar::Int len)
	{
		for (Liar::Int i = 0; i < len; ++i) ReadTypeVertex(pFile);
	}

	void NetGeometry::ReadTypeVertex(FILE* pFile)
	{
		Liar::Int type = 0;
		fread(&type, sizeof(Liar::Int), 1, pFile);
		Liar::VertexElementAttr vexType = static_cast<Liar::VertexElementAttr>(type);

		// 数组长度
		Liar::Int len = 0;
		fread(&len, sizeof(Liar::Int), 1, pFile);
		m_rawVertexBuffers->SetSubVertexBufferLen(vexType, len);

		if (vexType == Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY)
		{
			ReadIntHeapOperator(vexType, len, pFile);
		}
		else if (vexType == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_WEIGHTS || 
				 vexType == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_INDICES)
		{
			ReadSkinInfo(vexType, len, pFile);
		}
		else if (vexType == Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES)
		{
			size_t blockSize = sizeof(Liar::Uint);
			for (Liar::Int i = 0; i < len; ++i)
			{
				Liar::Int index = 0;
				fread(&index, blockSize, 1, pFile);
				m_rawVertexBuffers->SetRawIndex(i, index);
			}
		}
		else
		{
			Liar::VertexFormatType elementType = Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR2;
			switch (vexType)
			{
			case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			case Liar::VertexElementAttr::ELEMENT_ATTR_SCALE:
				elementType = Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR3;
				break;
			case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
				elementType = Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR2;
				break;
			case Liar::VertexElementAttr::ELEMENT_ATTR_ROTATION:
				elementType = Liar::VertexFormatType::VERTEX_FORMAT_TYPE_QUATERNION;
				break;
			default:
				elementType = Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR4;
				break;
			}

			for (Liar::Int i = 0; i < len; ++i)
			{
				void* vec = ReadFloatVector(elementType, pFile);
				m_rawVertexBuffers->SetSubVertexBuffer(vexType, i, vec);
			}
		}
	}

	void* NetGeometry::ReadFloatVector(Liar::VertexFormatType type, FILE* pFile)
	{
		size_t floatSize = sizeof(Liar::Number);
		switch (type)
		{
		case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR2:
		{
			Liar::Vector2* vec = new Liar::Vector2();
			fread(&(vec->x), floatSize, 1, pFile);
			fread(&(vec->y), floatSize, 1, pFile);
			return vec;
		}
		case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR3:
		{
			Liar::Vector3* vec = new Liar::Vector3();
			fread(&(vec->x), floatSize, 1, pFile);
			fread(&(vec->y), floatSize, 1, pFile);
			fread(&(vec->z), floatSize, 1, pFile);
			return vec;
		}
		case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR4:
		{
			Liar::Vector4* vec = new Liar::Vector4();
			fread(&(vec->x), floatSize, 1, pFile);
			fread(&(vec->y), floatSize, 1, pFile);
			fread(&(vec->z), floatSize, 1, pFile);
			fread(&(vec->w), floatSize, 1, pFile);
			return vec;
		}
		case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_QUATERNION:
		{
			Liar::Quaternion* vec = new Liar::Quaternion();
			fread(&(vec->x), floatSize, 1, pFile);
			fread(&(vec->y), floatSize, 1, pFile);
			fread(&(vec->z), floatSize, 1, pFile);
			fread(&(vec->w), floatSize, 1, pFile);
			return vec;
		}
		default:
			return nullptr;
		}
	}

	void NetGeometry::ReadIntHeapOperator(Liar::VertexElementAttr type, Liar::Int len, FILE* pFile)
	{
		size_t blockSize = sizeof(Liar::Int);

		Liar::Int perSize = 0;
		fread(&perSize, blockSize, 1, pFile);

		for (Liar::Int i = 0; i < len; ++i)
		{
			Liar::IntHeapOperator* it = new Liar::IntHeapOperator(perSize);
			for (Liar::Int j = 0; j < perSize; ++j) fread(&((*it)[j]), blockSize, 1, pFile);
			m_rawVertexBuffers->SetSubVertexBuffer(type, i, it);
		}
	}

	void NetGeometry::ReadSkinInfo(Liar::VertexElementAttr type, Liar::Int len, FILE* pFile)
	{
		size_t blockSize = sizeof(Liar::Int);
		Liar::Int perSize = 0;
		fread(&perSize, blockSize, 1, pFile);

		blockSize = sizeof(Liar::Number);
		for (Liar::Int i = 0; i < len; ++i)
		{
			Liar::Vector4* it = new Liar::Vector4();
			for (Liar::Int j = 0; j < perSize; ++j) fread(&((*it)[j]), blockSize, 1, pFile);
			m_rawVertexBuffers->SetSubVertexBuffer(type, i, it);
		}
	}
}