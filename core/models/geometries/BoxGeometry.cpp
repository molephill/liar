
#include <core/models/geometries/BoxGeometry.h>
#include <Liar3D.h>

namespace Liar
{
	BoxGeometry::BoxGeometry(Liar::Number l, Liar::Number w, Liar::Number h):
		Liar::Geometry(),
		m_long(l), m_width(w), m_height(h)
	{
	}


	BoxGeometry::~BoxGeometry()
	{
		Destroy();
	}

	void BoxGeometry::SetLong(Liar::Number value)
	{
		if (m_long != value)
		{
			m_long = value;
			ReleaseResource();
			ActiveResource();
		}
	}

	void BoxGeometry::SetWidth(Liar::Number value)
	{
		if (m_width != value)
		{
			m_width = value;
			ReleaseResource();
			ActiveResource();
		}
	}

	void BoxGeometry::SetHeight(Liar::Number value)
	{
		if (m_height != value)
		{
			m_height = value;
			ReleaseResource();
			ActiveResource();
		}
	}

	void BoxGeometry::VertexAttrbPointer()
	{
		Liar::StageContext& gl = *(Liar::Liar3D::renderState->stageContext);
		size_t stride = Liar::VertexElementSize::ELEMENT_SIZE_VECTOR3 * 2 + Liar::VertexElementSize::ELEMENT_SIZE_VECTOR2;
		size_t positionOffsize = 0;
		size_t normalOffsize = positionOffsize + Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3;
		size_t texCoordOffseize = normalOffsize + Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3;
		// position
		gl.VertexAttribPointer(0, Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3, GL_FLOAT, GL_FALSE, stride, (void*)positionOffsize);
		gl.EnableVertexAttribArray(0);
		// normal
		gl.VertexAttribPointer(1, Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR3, GL_FLOAT, GL_FALSE, stride, (void*)normalOffsize);
		gl.EnableVertexAttribArray(1);
		// texCoordinate
		gl.VertexAttribPointer(2, Liar::VertexElementFormat::ELEMENT_FORMAT_VECTOR2, GL_FLOAT, GL_FALSE, stride, (void*)texCoordOffseize);
		gl.EnableVertexAttribArray(2);
	}

	//void BoxGeometry::RecreateResource()
	//{
	//	Liar::Resource::RecreateResource();
	//	m_rawVertexBuffers = Liar::Liar3D::geometryFactory->GetVertexFactory().GetRawVertexBuffers(m_geometryVertexType);
	//	Liar::Number halfLong = m_long * 0.5f;
	//	Liar::Number halfWidth = m_width * 0.5f;
	//	Liar::Number halfHeight = m_height * 0.5f;

	//	GLfloat vertices[] = {
	//		-halfLong, halfHeight, -halfWidth, 0, 1, 0, 0, 0, 
	//	  halfLong, halfHeight, -halfWidth, 0, 1, 0, 1, 0, 
	//	  halfLong, halfHeight, halfWidth, 0, 1, 0, 1, 1, 
	//		-halfLong, halfHeight, halfWidth, 0, 1, 0, 0, 1,
	//		//下
	//		-halfLong, -halfHeight, -halfWidth, 0, -1, 0, 0, 1, 
	//		halfLong, -halfHeight, -halfWidth, 0, -1, 0, 1, 1, 
	//		halfLong, -halfHeight, halfWidth, 0, -1, 0, 1, 0, 
	//		-halfLong, -halfHeight, halfWidth, 0, -1, 0, 0, 0,
	//		//左
	//		-halfLong, halfHeight, -halfWidth, -1, 0, 0, 0, 0, 
	//		-halfLong, halfHeight, halfWidth, -1, 0, 0, 1, 0, 
	//		-halfLong, -halfHeight, halfWidth, -1, 0, 0, 1, 1, 
	//		-halfLong, -halfHeight, -halfWidth, -1, 0, 0, 0, 1,
	//		//右
	//		halfLong, halfHeight, -halfWidth, 1, 0, 0, 1, 0, 
	//		halfLong, halfHeight, halfWidth, 1, 0, 0, 0, 0, 
	//		halfLong, -halfHeight, halfWidth, 1, 0, 0, 0, 1, 
	//		halfLong, -halfHeight, -halfWidth, 1, 0, 0, 1, 1,
	//		//前
	//		-halfLong, halfHeight, halfWidth, 0, 0, 1, 0, 0, 
	//		halfLong, halfHeight, halfWidth, 0, 0, 1, 1, 0, 
	//		halfLong, -halfHeight, halfWidth, 0, 0, 1, 1, 1, 
	//		-halfLong, -halfHeight, halfWidth, 0, 0, 1, 0, 1,
	//		//后
	//		-halfLong, halfHeight, -halfWidth, 0, 0, -1, 1, 0, 
	//		halfLong, halfHeight, -halfWidth, 0, 0, -1, 0, 0, 
	//		halfLong, -halfHeight, -halfWidth, 0, 0, -1, 0, 1, 
	//		-halfLong, -halfHeight, -halfWidth, 0, 0, -1, 1, 1
	//	};
	//	GLuint indices[] = {  // Note that we start from 0!
	//						  //上
	//		0, 1, 2, 2, 3, 0,
	//		//下
	//		4, 7, 6, 6, 5, 4,
	//		//左
	//		8, 9, 10, 10, 11, 8,
	//		//右
	//		12, 15, 14, 14, 13, 12,
	//		//前
	//		16, 17, 18, 18, 19, 16,
	//		//后
	//		20, 23, 22, 22, 21, 20
	//	};

	//	glGenVertexArrays(1, &m_vertexArray);
	//	glGenBuffers(1, &m_vertexBuffer);
	//	glGenBuffers(1, &m_elementBuffer);
	//	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	//	glBindVertexArray(m_vertexArray);

	//	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(Liar::Uint), indices, GL_STATIC_DRAW);

	//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	//	glEnableVertexAttribArray(0);
	//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)3);
	//	glEnableVertexAttribArray(1);
	//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)6);
	//	glEnableVertexAttribArray(2);

	//	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	//	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/ar
	//}

	//void BoxGeometry::RecreateSubResource() {}

	void BoxGeometry::RecreateSubResource()
	{
		Liar::Number halfLong = m_long * 0.5f;
		Liar::Number halfWidth = m_width * 0.5f;
		Liar::Number halfHeight = m_height * 0.5f;

		// positions
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, -halfLong, -halfHeight, halfWidth);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, -halfLong, -halfHeight, -halfWidth);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, halfLong, -halfHeight, halfWidth);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, halfLong, -halfHeight, -halfWidth);

		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, -halfLong, halfHeight, halfWidth);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, -halfLong, halfHeight, -halfWidth);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, halfLong, halfHeight, halfWidth);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, halfLong, halfHeight, -halfWidth);

		// normals
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 0, 1, 0);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 0, -1, 0);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, -1, 0, 0);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 1, 0, 0);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 0, 0, 1);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 0, 0, -1);

		// texCoords
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 0, 0);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 1, 0);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 1, 1);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 0, 1);

		m_rawVertexBuffers->SetIndicesLength(36);
		m_rawVertexBuffers->SetIndex(0, 0);
		m_rawVertexBuffers->SetIndex(1, 1);
		m_rawVertexBuffers->SetIndex(2, 2);
		m_rawVertexBuffers->SetIndex(3, 1);
		m_rawVertexBuffers->SetIndex(4, 0);
		m_rawVertexBuffers->SetIndex(5, 4);
		m_rawVertexBuffers->SetIndex(6, 6);
		m_rawVertexBuffers->SetIndex(7, 7);
		m_rawVertexBuffers->SetIndex(8, 8);
		m_rawVertexBuffers->SetIndex(9, 7);
		m_rawVertexBuffers->SetIndex(10, 6);
		m_rawVertexBuffers->SetIndex(11, 10);
		m_rawVertexBuffers->SetIndex(12, 12);
		m_rawVertexBuffers->SetIndex(13, 13);
		m_rawVertexBuffers->SetIndex(14, 14);
		m_rawVertexBuffers->SetIndex(15, 13);
		m_rawVertexBuffers->SetIndex(16, 12);
		m_rawVertexBuffers->SetIndex(17, 16);
		m_rawVertexBuffers->SetIndex(18, 18);
		m_rawVertexBuffers->SetIndex(19, 19);
		m_rawVertexBuffers->SetIndex(20, 20);
		m_rawVertexBuffers->SetIndex(21, 19);
		m_rawVertexBuffers->SetIndex(22, 18);
		m_rawVertexBuffers->SetIndex(23, 22);
		m_rawVertexBuffers->SetIndex(24, 24);
		m_rawVertexBuffers->SetIndex(25, 25);
		m_rawVertexBuffers->SetIndex(26, 26);
		m_rawVertexBuffers->SetIndex(27, 25);
		m_rawVertexBuffers->SetIndex(28, 24);
		m_rawVertexBuffers->SetIndex(29, 28);
		m_rawVertexBuffers->SetIndex(30, 30);
		m_rawVertexBuffers->SetIndex(31, 31);
		m_rawVertexBuffers->SetIndex(32, 32);
		m_rawVertexBuffers->SetIndex(33, 31);
		m_rawVertexBuffers->SetIndex(34, 30);
		m_rawVertexBuffers->SetIndex(35, 34);

		// 顶点索引数据
		m_rawVertexBuffers->SetVertexKeyLength(35);
		SetVertexKey(0, 0);
		SetVertexKey(1, 3);
		SetVertexKey(2, 2);
		SetVertexKey(3, 0);
		SetVertexKey(4, 1);
		SetVertexKey(5, 0);
		SetVertexKey(6, 4);
		SetVertexKey(7, 7);
		SetVertexKey(8, 5);
		SetVertexKey(9, 0);
		SetVertexKey(10, 6);
		SetVertexKey(11, 0);
		SetVertexKey(12, 0);
		SetVertexKey(13, 5);
		SetVertexKey(14, 1);
		SetVertexKey(15, 0);
		SetVertexKey(16, 4);
		SetVertexKey(17, 0);
		SetVertexKey(18, 1);
		SetVertexKey(19, 7);
		SetVertexKey(20, 3);
		SetVertexKey(21, 0);
		SetVertexKey(22, 5);
		SetVertexKey(23, 0);
		SetVertexKey(24, 3);
		SetVertexKey(25, 6);
		SetVertexKey(26, 2);
		SetVertexKey(27, 0);
		SetVertexKey(28, 7);
		SetVertexKey(29, 0);
		SetVertexKey(30, 2);
		SetVertexKey(31, 4);
		SetVertexKey(32, 0);
		SetVertexKey(33, 0);
		SetVertexKey(34, 6);
	}

	void BoxGeometry::SetVertexKey(Liar::Int index, Liar::Uint posIndex, Liar::Uint normalIndex, Liar::Uint texIndex)
	{
		Liar::IVertexKey* key = PopVertexKey();
		key->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, posIndex);
		key->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, normalIndex);
		key->SetVertexIndex(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, texIndex);
		m_rawVertexBuffers->SetVertexKey(index, key);
	}
}