
#include <core/models/geometries/NetGeometry.h>
#include <Liar3D.h>

namespace Liar
{
	NetGeometry::NetGeometry():
		Liar::Geometry(),
		Liar::ITickRender(),
		m_url(""), m_loopStep(0)
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

	bool NetGeometry::RecreateSubResource()
	{
		std::string realPath = Liar::Liar3D::urlFormat->FormatSourceURL(m_url.c_str());

		m_byteArray = Liar::Liar3D::LiarLoad(realPath.c_str());

		Liar::Int type = m_byteArray->ReadInt();
		m_geometryVertexType = static_cast<Liar::GeometryVertexType>(type);
		m_rawVertexBuffers = Liar::Liar3D::geometryFactory->GetVertexFactory().GetRawVertexBuffers(m_geometryVertexType);
		Liar::Int mtlIndex = m_byteArray->ReadInt();
		m_rawVertexBuffers->SetMtlIndex(mtlIndex);

		Liar::Liar3D::tickRender->AddTickRender(this);

		/*std::ofstream out("C:/Users/Administrator/Desktop/model/out1.txt");
		m_rawVertexBuffers->Print(out);
		out.close();*/

		return false;
	}

	bool NetGeometry::TickRender(void* args, Liar::Int delSec)
	{
		Liar::Int loopCount = 0;
		switch (m_geometryVertexType)
		{
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL:
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_COLOR:
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_TEXTURE:
			loopCount = 4;
			break;
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR:
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_TEXTURE_SKIN:
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE:
			loopCount = 5;
			break;
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR_TEXTURE:
			loopCount = 6;
			break;
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR_SKIN:
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE_SKIN:
			loopCount = 7;
			break;
		case Liar::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_COLOR_TEXTURE_SKIN:
			loopCount = 8;
			break;
		default:
			break;
		}

		Liar::RenderState& state = *(Liar::Liar3D::renderState);
		while (m_loopStep < loopCount)
		{
			ParseSubRawData();
			++m_loopStep;
			if (Liar::Liar3D::GetTimer() - state.lastCurrentTime >= delSec) return false;
		}
		UploadData();
		return true;
	}

	void NetGeometry::ParseSubRawData()
	{
		Liar::Int type = m_byteArray->ReadInt();
		Liar::VertexElementAttr vexType = static_cast<Liar::VertexElementAttr>(type);

		// 数组长度
		Liar::Int len = m_byteArray->ReadInt();
		m_rawVertexBuffers->SetSubVertexBufferLen(vexType, len);

		if (vexType == Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY)
		{
			ParseIntHeapOperator(vexType, len);
		}
		else if (vexType == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_WEIGHTS ||
			vexType == Liar::VertexElementAttr::ELEMENT_ATTR_BONE_INDICES)
		{
			ParseSkinData(vexType, len);
		}
		else if (vexType == Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES)
		{
			for (Liar::Int i = 0; i < len; ++i)
			{
				Liar::Int index = m_byteArray->RadUnsignedInt();
				m_rawVertexBuffers->SetRawIndex(i, index);
			}
		}
		else
		{
			Liar::VertexFormatType elementType = Liar::Liar3D::ElementAttrFormat(vexType);
			for (Liar::Int i = 0; i < len; ++i)
			{
				void* vec = Liar::Liar3D::ParseVector(m_byteArray, elementType);
				m_rawVertexBuffers->SetSubVertexBuffer(vexType, i, vec);
			}
		}
	}

	void NetGeometry::ParseIntHeapOperator(Liar::VertexElementAttr type, Liar::Int len)
	{
		Liar::Int perSize = m_byteArray->ReadInt();

		for (Liar::Int i = 0; i < len; ++i)
		{
			Liar::IntHeapOperator* it = new Liar::IntHeapOperator(perSize);
			for (Liar::Int j = 0; j < perSize; ++j) (*it)[j] = m_byteArray->ReadInt();
			m_rawVertexBuffers->SetSubVertexBuffer(type, i, it);
		}
	}

	void NetGeometry::ParseSkinData(Liar::VertexElementAttr type, Liar::Int len)
	{
		Liar::Int perSize = m_byteArray->ReadInt();
		for (Liar::Int i = 0; i < len; ++i)
		{
			Liar::Vector4* it = new Liar::Vector4();
			for (Liar::Int j = 0; j < perSize; ++j) (*it)[j] = m_byteArray->ReadFloat();
			m_rawVertexBuffers->SetSubVertexBuffer(type, i, it);
		}
	}
}