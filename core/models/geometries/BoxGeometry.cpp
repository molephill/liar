
#include <core/models/geometries/BoxGeometry.h>
#include <core/graphics/VertexBufferPositionNormalTexture.h>

namespace Liar
{
	BoxGeometry::BoxGeometry(Liar::Number l, Liar::Number w, Liar::Number h):
		Liar::Geometry(Liar::GeometryVertexType::GEOMETRY_VERTEX_TYPE_POSITION_NORMAL_TEXTURE),
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

	void BoxGeometry::InitVertices(Liar::Uint size)
	{
		m_numberVertices = size;
		// vertices;
		Liar::VertexBufferPositionNormalTexture** vertices = (Liar::VertexBufferPositionNormalTexture**)malloc(sizeof(Liar::VertexBufferPositionNormalTexture*)*m_numberVertices);
		for (size_t i = 0; i < m_numberVertices; ++i)
		{
			vertices[i] = new Liar::VertexBufferPositionNormalTexture();
		}
		m_vertices = (Liar::IVertexBuffer**)vertices;
	}

	void BoxGeometry::RecreateResource()
	{

		//Liar::Number halfLong = m_long * 0.5f;
		//Liar::Number halfWidth = m_width * 0.5f;
		//Liar::Number halfHeight = m_height * 0.5f;

		//GLfloat vertices[] = {
		//	-halfLong, halfHeight, -halfWidth, 0, 1, 0, 0, 0, halfLong, halfHeight, -halfWidth, 0, 1, 0, 1, 0, halfLong, halfHeight, halfWidth, 0, 1, 0, 1, 1, -halfLong, halfHeight, halfWidth, 0, 1, 0, 0, 1,
		//	//下
		//	-halfLong, -halfHeight, -halfWidth, 0, -1, 0, 0, 1, halfLong, -halfHeight, -halfWidth, 0, -1, 0, 1, 1, halfLong, -halfHeight, halfWidth, 0, -1, 0, 1, 0, -halfLong, -halfHeight, halfWidth, 0, -1, 0, 0, 0,
		//	//左
		//	-halfLong, halfHeight, -halfWidth, -1, 0, 0, 0, 0, -halfLong, halfHeight, halfWidth, -1, 0, 0, 1, 0, -halfLong, -halfHeight, halfWidth, -1, 0, 0, 1, 1, -halfLong, -halfHeight, -halfWidth, -1, 0, 0, 0, 1,
		//	//右
		//	halfLong, halfHeight, -halfWidth, 1, 0, 0, 1, 0, halfLong, halfHeight, halfWidth, 1, 0, 0, 0, 0, halfLong, -halfHeight, halfWidth, 1, 0, 0, 0, 1, halfLong, -halfHeight, -halfWidth, 1, 0, 0, 1, 1,
		//	//前
		//	-halfLong, halfHeight, halfWidth, 0, 0, 1, 0, 0, halfLong, halfHeight, halfWidth, 0, 0, 1, 1, 0, halfLong, -halfHeight, halfWidth, 0, 0, 1, 1, 1, -halfLong, -halfHeight, halfWidth, 0, 0, 1, 0, 1,
		//	//后
		//	-halfLong, halfHeight, -halfWidth, 0, 0, -1, 1, 0, halfLong, halfHeight, -halfWidth, 0, 0, -1, 0, 0, halfLong, -halfHeight, -halfWidth, 0, 0, -1, 0, 1, -halfLong, -halfHeight, -halfWidth, 0, 0, -1, 1, 1
		//};
		//GLuint indices[] = {  // Note that we start from 0!
		//					  //上
		//	0, 1, 2, 2, 3, 0,
		//	//下
		//	4, 7, 6, 6, 5, 4,
		//	//左
		//	8, 9, 10, 10, 11, 8,
		//	//右
		//	12, 15, 14, 14, 13, 12,
		//	//前
		//	16, 17, 18, 18, 19, 16,
		//	//后
		//	20, 23, 22, 22, 21, 20
		//};

		//m_numberIndices = 36;

		//m_indices = (Liar::Uint*)malloc(sizeof(Liar::Uint)*m_numberIndices);
		//m_indices[0] = 0; m_indices[1] = 1; m_indices[2] = 3; m_indices[3] = 1; m_indices[4] = 2; m_indices[5] = 3;

		//glGenVertexArrays(1, &m_vertexArray);
		//glGenBuffers(1, &m_vertexBuffer);
		//glGenBuffers(1, &m_elementBuffer);
		//// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		//glBindVertexArray(m_vertexArray);

		//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numberIndices * sizeof(Liar::Uint), indices, GL_STATIC_DRAW);

		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)3);
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)6);
		//glEnableVertexAttribArray(2);

		//glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		//glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/ar

		//return;

		Liar::Geometry::RecreateResource();
		InitVertices(24);

		m_numberIndices = 36;

		Liar::Number halfLong = m_long * 0.5f;
		Liar::Number halfWidth = m_width * 0.5f;
		Liar::Number halfHeight = m_height * 0.5f;

		// positions
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, -halfLong, halfHeight, -halfWidth);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, halfLong, halfHeight, -halfWidth);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, halfLong, halfHeight, halfWidth);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, -halfLong, halfHeight, halfWidth);

		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, -halfLong, -halfHeight, -halfWidth);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, halfLong, -halfHeight, -halfWidth);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, halfLong, -halfHeight, halfWidth);
		m_rawVertexBuffers->AddSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, -halfLong, -halfHeight, halfWidth);

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

		Liar::IVertexBuffer* vertex = nullptr;
		// 上
		vertex = m_vertices[0];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 0));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 0));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 0));

		vertex = m_vertices[1];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 1));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 0));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 1));

		vertex = m_vertices[2];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 2));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 0));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 2));

		vertex = m_vertices[3];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 3));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 0));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 3));

		// 下
		vertex = m_vertices[4];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 4));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 1));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 3));

		vertex = m_vertices[5];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 5));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 1));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 2));

		vertex = m_vertices[6];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 6));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 1));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 1));

		vertex = m_vertices[7];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 7));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 1));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 0));

		// 左
		vertex = m_vertices[8];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 0));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 2));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 0));

		vertex = m_vertices[9];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 3));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 2));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 1));

		vertex = m_vertices[10];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 7));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 2));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 2));

		vertex = m_vertices[11];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 4));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 2));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 3));

		// 右
		vertex = m_vertices[12];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 1));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 3));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 1));

		vertex = m_vertices[13];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 2));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 3));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 0));

		vertex = m_vertices[14];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 6));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 3));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 3));

		vertex = m_vertices[15];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 5));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 3));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 2));

		// 前
		vertex = m_vertices[16];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 3));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 4));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 0));

		vertex = m_vertices[17];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 2));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 4));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 1));

		vertex = m_vertices[18];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 6));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 4));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 2));

		vertex = m_vertices[19];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 7));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 4));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 3));

		// 后
		vertex = m_vertices[20];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 0));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 5));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 1));

		vertex = m_vertices[21];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 1));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 5));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 0));

		vertex = m_vertices[22];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 5));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 5));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 3));

		vertex = m_vertices[23];
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_POSITION, 4));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_NORMAL, 5));
		vertex->SetAttrData(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, m_rawVertexBuffers->GetSubVertexBuffer(Liar::VertexElementAttr::ELEMENT_ATTR_TEXTURECOORDINATE, 2));

		// indices
		m_indices = (Liar::Uint*)malloc(sizeof(Liar::Uint)*m_numberIndices);
		// 上
		m_indices[0] = 0; m_indices[1] = 1; m_indices[2] = 2; m_indices[3] = 2; m_indices[4] = 3; m_indices[5] = 0;
		// 下
		m_indices[6] = 4; m_indices[7] = 7; m_indices[8] = 6; m_indices[9] = 8; m_indices[10] = 5; m_indices[11] = 4;
		// 左
		m_indices[12] = 8; m_indices[13] = 9; m_indices[14] = 10; m_indices[15] = 10; m_indices[16] = 11; m_indices[17] = 8;
		// 右
		m_indices[18] = 12; m_indices[19] = 15; m_indices[20] = 14; m_indices[21] = 14; m_indices[22] = 13; m_indices[23] = 12;
		// 前
		m_indices[24] = 16; m_indices[25] = 17; m_indices[26] = 18; m_indices[27] = 18; m_indices[28] = 19; m_indices[29] = 16;
		// 后
		m_indices[30] = 20; m_indices[31] = 23; m_indices[32] = 22; m_indices[33] = 22; m_indices[34] = 21; m_indices[35] = 20;

		// 开始绑定
		GenAndBindVertex();
	}
}