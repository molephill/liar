#include <core/ani/Skeleton.h>
#include <Liar3D.h>

namespace Liar
{
	Skeleton::Skeleton() :
		Liar::Resource(),
		Liar::ITickRender(),
		m_url(""),
		m_bones(nullptr), m_numberBones(0),
		m_parseVer(0), m_loopStep(0), m_byteArray(nullptr),
		m_positions(nullptr), m_numberPositons(0),
		m_rotations(nullptr), m_numberRotations(0),
		m_scales(nullptr), m_numberScales(0)
	{
	}

	Skeleton::~Skeleton()
	{
		Destroy();
	}

	Liar::Boolen Skeleton::Equals(const Liar::Skeleton& ske) const
	{
		return Equals(ske.m_url.c_str());
	}

	Liar::Boolen Skeleton::Equals(const char* name) const
	{
		return m_url == name;
	}

	void Skeleton::SetURL(const char* url)
	{
		if (m_url != url)
		{
			m_url = url;
			DisposeResource();
			RecreateResource();
		}
	}

	void Skeleton::RecreateResource()
	{
		Liar::Resource::RecreateResource();
		std::string realPath = Liar::Liar3D::urlFormat->FormatSkeletonURL(m_url.c_str()) + ".SKE";//Liar::skeSzChar;
		m_byteArray = Liar::Liar3D::LiarLoad(realPath.c_str());
		if (m_byteArray)
		{
			m_numberBones = m_byteArray->ReadInt();
			m_bones = (Liar::Bone**)malloc(sizeof(Liar::Bone*)*m_numberBones);
			for (Liar::Int i = 0; i < m_numberBones; ++i) m_bones[i] = nullptr;
			Liar::Liar3D::tickRender->AddTickRender(this);
		}
	}

	void Skeleton::DisposeResource()
	{
		if (m_byteArray)
		{
			if (m_byteArray->GetBytesAvailable() > 0) Liar::Liar3D::tickRender->RemoveTickRender(this);
			delete m_byteArray;
			m_byteArray = nullptr;
		}

		Liar::Int i = 0;
		if (m_bones)
		{
			for (i = 0; i < m_numberBones; ++i)
			{
				if (m_bones[i]) delete m_bones[i];
			}
			free(m_bones);
			m_bones = nullptr;
		}

		if (m_positions)
		{
			for (i = 0; i < m_numberPositons; ++i)
			{
				if (m_positions[i]) delete m_positions[i];
			}
			free(m_positions);
			m_positions = nullptr;
		}

		if (m_rotations)
		{
			for (i = 0; i < m_numberRotations; ++i)
			{
				if (m_rotations[i]) delete m_rotations[i];
			}
			free(m_rotations);
			m_rotations = nullptr;
		}

		if (m_scales)
		{
			for (i = 0; i < m_numberScales; ++i)
			{
				if (m_scales[i]) delete m_scales[i];
			}
			free(m_scales);
			m_scales = nullptr;
		}
	}

	bool Skeleton::TickRender(void* args, Liar::Int delSec)
	{
		if (m_parseVer == 0)
		{
			return ParseBones(m_byteArray, delSec);
		}
		else
		{
			Liar::RenderState& state = *(Liar::Liar3D::renderState);
			while (m_parseVer < 4)
			{
				ParseMatrixInfo(m_byteArray, delSec);
				if (Liar::Liar3D::GetTimer() - state.lastCurrentTime >= delSec) return false;
			}
			return true;
		}
	}

	Liar::Boolen Skeleton::ParseBones(Liar::ByteArray* byte, Liar::Int delSec)
	{
		Liar::RenderState& state = *(Liar::Liar3D::renderState);
		while (m_loopStep < m_numberBones)
		{
			Liar::Bone* bone = new Liar::Bone();
			std::string name = byte->ReadString();
			Liar::Int parentIndex = byte->ReadInt();
			Liar::Int positionIndex = byte->ReadInt();
			Liar::Int rotationIndex = byte->ReadInt();
			Liar::Int scaleIndex = byte->ReadInt();
			bone->SetName(name.c_str());
			bone->SetMatrixKey(positionIndex, rotationIndex, scaleIndex);
			bone->SetParentIndex(parentIndex);
			m_bones[m_loopStep++] = bone;
			if (Liar::Liar3D::GetTimer() - state.lastCurrentTime >= delSec) return false;
		}
		m_loopStep = 0;
		++m_parseVer;
		return false;
	}

	Liar::Boolen Skeleton::ParseMatrixInfo(Liar::ByteArray* byte, Liar::Int delSce)
	{
		Liar::Int type = byte->ReadInt();
		Liar::VertexElementAttr attrType = static_cast<Liar::VertexElementAttr>(type);
		Liar::VertexFormatType elementType = Liar::Liar3D::ElementAttrFormat(attrType);

		Liar::Int size = byte->ReadInt();
		SetMatrixInfoLen(attrType, size);

		for (Liar::Int i = 0; i < size; ++i)
		{
			void* data = Liar::Liar3D::ParseVector(byte, elementType);
			SetMatrixInfo(attrType, i, data);
		}
		++m_parseVer;
		return false;
	}

	void Skeleton::SetMatrixInfoLen(Liar::VertexElementAttr type, Liar::Int len)
	{
		switch (type)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			m_numberPositons = len;
			m_positions = (Liar::Vector3**)malloc(sizeof(Liar::Vector3*)*len);
			for (Liar::Int i = 0; i < len; ++i) m_positions[i] = nullptr;
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_ROTATION:
			m_numberRotations = len;
			m_rotations = (Liar::Quaternion**)malloc(sizeof(Liar::Quaternion*)*len);
			for (Liar::Int i = 0; i < len; ++i) m_rotations[i] = nullptr;
			break;
		default:
			m_numberScales = len;
			m_scales = (Liar::Vector3**)malloc(sizeof(Liar::Vector3*)*len);
			for (Liar::Int i = 0; i < len; ++i) m_scales[i] = nullptr;
			break;
		}
	}

	void Skeleton::SetMatrixInfo(Liar::VertexElementAttr type, Liar::Int index, void* data)
	{
		switch (type)
		{
		case Liar::VertexElementAttr::ELEMENT_ATTR_POSITION:
			m_positions[index] = static_cast<Liar::Vector3*>(data);
			break;
		case Liar::VertexElementAttr::ELEMENT_ATTR_ROTATION:
			m_rotations[index] = static_cast<Liar::Quaternion*>(data);
			break;
		default:
			m_scales[index] = static_cast<Liar::Vector3*>(data);
			break;
		}
	}
}
