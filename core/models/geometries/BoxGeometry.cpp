
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
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, new Liar::Vector3(-halfLong, -halfHeight, halfWidth));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, new Liar::Vector3(-halfLong, -halfHeight, -halfWidth));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, new Liar::Vector3(halfLong, -halfHeight, halfWidth));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, new Liar::Vector3(halfLong, -halfHeight, -halfWidth));

		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, new Liar::Vector3(-halfLong, halfHeight, halfWidth));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, new Liar::Vector3(-halfLong, halfHeight, -halfWidth));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, new Liar::Vector3(halfLong, halfHeight, halfWidth));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, new Liar::Vector3(halfLong, halfHeight, -halfWidth));

		// normals
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, new Liar::Vector3(0, 1, 0));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, new Liar::Vector3(0, -1, 0));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, new Liar::Vector3(-1, 0, 0));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, new Liar::Vector3(1, 0, 0));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, new Liar::Vector3(0, 0, 1));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, new Liar::Vector3(0, 0, -1));

		// texCoords
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, new Liar::Vector2(0, 0));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, new Liar::Vector2(1, 0));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, new Liar::Vector2(1, 1));
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, new Liar::Vector2(0, 1));

		//m_rawVertexBuffers->SetSubVertexBufferLen(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 36);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 0, 0);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 1, 1);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 2, 2);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 3, 2);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 4, 3);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 5, 0);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 6, 4);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 7, 5);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 8, 6);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 9, 6);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 10, 7);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 11, 4);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 12, 8);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 13, 9);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 14, 10);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 15, 10);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 16, 11);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 17, 8);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES,+ 18, 12);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 19, 13);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 20, 14);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 21, 14);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 22, 15);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 23, 12);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 24, 16);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 25, 17);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 26, 18);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 27, 18);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 28, 19);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 29, 16);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 30, 20);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 31, 21);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 32, 22);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 33, 22);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 34, 23);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_INDICES, 35, 20);

		//// 顶点索引数据
		//m_rawVertexBuffers->SetSubVertexBufferLen(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 24);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 0, 0, 0, 0);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 1, 1, 0, 1);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 2, 2, 0, 2);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 3, 3, 0, 3);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 4, 4, 1, 3);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 5, 5, 1, 0);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 6, 6, 1, 1);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 7, 7, 1, 2);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 8, 0, 2, 3);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 9, 3, 2, 0);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 10, 5, 2, 1);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 11, 4, 2, 2);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 12, 3, 3, 3);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 13, 2, 3, 0);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 14, 6, 3, 1);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 15, 5, 3, 2);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 16, 2, 4, 3);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 17, 1, 4, 0);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 18, 7, 4, 1);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 19, 6, 4, 2);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 20, 1, 5, 3);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 21, 0, 5, 0);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 22, 4, 5, 1);
		//m_rawVertexBuffers->SetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_RAW_KEY, 23, 7, 5, 2);
	}
}