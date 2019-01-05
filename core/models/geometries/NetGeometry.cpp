
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
		m_url = url;
		DisposeResource();
		RecreateResource();
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
		ReadTypeVertex(pFile);			// positions
		ReadTypeVertex(pFile);			// normals
		ReadTypeVertex(pFile);			// texCoords
		ReadTypeVertex(pFile);			// colors
		ReadTypeVertex(pFile);			// keys
		ReadTypeVertex(pFile);			// indices
		// 引用材质索引
		Liar::Int mtlIndex = 0;
		fread(&mtlIndex, sizeof(Liar::Int), 1, pFile);
		m_rawVertexBuffers->SetMtlIndex(mtlIndex);

		fclose(pFile);
	}

	void NetGeometry::ReadTypeVertex(FILE* pFile)
	{
		Liar::Int type = 0;
		fread(&type, sizeof(Liar::Int), 1, pFile);
		Liar::VertexElementAttr vexType = static_cast<Liar::VertexElementAttr>(type);

		Liar::Int len = 0;
		fread(&len, sizeof(Liar::Int), 1, pFile);
		m_rawVertexBuffers->SetSubVertexBufferLen(vexType, len);
		for (Liar::Int i = 0; i < len; ++i)
		{
			ReadTypeVertex(vexType, i, pFile);
		}
	}

	void NetGeometry::ReadTypeVertex(Liar::VertexElementAttr attr, Liar::Int index, FILE* pFile)
	{
		if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES)
		{
			Liar::Uint x = 0;
			fread(&x, sizeof(Liar::Uint), 1, pFile);
			m_rawVertexBuffers->SetSubVertexBuffer(attr, index, x);
		}
		else if (attr == Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY)
		{
			Liar::Int x = 0;
			Liar::Int y = 0;
			Liar::Int z = 0;
			Liar::Int w = 0;
			size_t strip = sizeof(Liar::Int);
			fread(&x, strip, 1, pFile);
			fread(&y, strip, 1, pFile);
			fread(&z, strip, 1, pFile);
			fread(&w, strip, 1, pFile);
			m_rawVertexBuffers->SetSubVertexBuffer(attr, index, x, y, z, w);
		}
		else
		{
			Liar::Number x = 0.0f;
			Liar::Number y = 0.0f;
			size_t len = sizeof(Liar::Number);

			fread(&x, len, 1, pFile);
			fread(&y, len, 1, pFile);

			switch (attr)
			{
			case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			case Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL:
			case Liar::VertexElementAttr::ELEMENT_ATTR_COLOR:
			{
				Liar::Number z = 0.0f;
				fread(&z, len, 1, pFile);
				m_rawVertexBuffers->SetSubVertexBuffer(attr, index, x, y, z);
				break;
			}
			case Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE:
			{
				m_rawVertexBuffers->SetSubVertexBuffer(attr, index, x, y);
				break;
			}
			case Liar::VertexElementAttr::ELEMENT_ATTR_ROTATION:
			{
				Liar::Number z = 0.0f;
				Liar::Number w = 0.0f;
				fread(&z, len, 1, pFile);
				fread(&w, len, 1, pFile);
				m_rawVertexBuffers->SetSubVertexBuffer(attr, index, x, y, z, w);
				break;
			}
			default:
				break;
			}
		}
	}
}