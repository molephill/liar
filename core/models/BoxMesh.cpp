
#include <core/models/BoxMesh.h>
#include <Liar3D.h>

namespace Liar
{
	BoxMesh::BoxMesh(Liar::Number l, Liar::Number w, Liar::Number h):
		Liar::BaseMesh(),
		m_long(l), m_width(w), m_height(h)
	{
		m_rawVertexBuffers = Liar::Liar3D::vertexFactory->GetRawVertexBuffers(Liar::MeshVertexType::MESH_VERTEX_TYPE_POSITION_NORMAL_TEXTURE);
	}

	BoxMesh::~BoxMesh()
	{

	}

	void BoxMesh::SetLong(Liar::Number value)
	{
		if (m_long != value)
		{
			m_long = value;
			ReleaseResource();
			ActiveResource();
		}
	}

	void BoxMesh::SetWidth(Liar::Number value)
	{
		if (m_width != value)
		{
			m_width = value;
			ReleaseResource();
			ActiveResource();
		}
	}

	void BoxMesh::SetHeight(Liar::Number value)
	{
		if (m_height != value)
		{
			m_height = value;
			ReleaseResource();
			ActiveResource();
		}
	}

	void BoxMesh::RecreateResource()
	{
		m_numberVertices = 24;
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

		// vertices;
		Liar::VertexBufferPositionNormalTexture** vertices = (Liar::VertexBufferPositionNormalTexture**)malloc(sizeof(Liar::VertexBufferPositionNormalTexture*)*m_numberVertices);
		m_vertices = (IVertexBuffer**)vertices;

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
	}

	void BoxMesh::Render(Liar::RenderState&)
	{
		Liar::StageContext& gl = *(Liar::Liar3D::stageContext);
		gl.DrawElements(GL_TRIANGLES, m_numberIndices, GL_UNSIGNED_INT, 0);
		gl.BindVertexArray(0);
	}
}