#pragma once

#include <core/graphics/raws/IRawVertexBuffers.h>

namespace Liar
{
	class RawVertexBuffersPositionNormalTexture :public Liar::IRawVertexBuffers
	{
	public:
		RawVertexBuffersPositionNormalTexture() :
			Liar::IRawVertexBuffers(),
			m_positons(nullptr), m_numberPostions(0),
			m_normals(nullptr), m_numberNormals(0),
			m_texCoords(nullptr), m_numberTexCoodrs(0)
		{
		};
		~RawVertexBuffersPositionNormalTexture() {};

	private:
		Liar::Vector3** m_positons;
		Liar::Uint m_numberPostions;

		Liar::Vector3** m_normals;
		Liar::Uint m_numberNormals;

		Liar::Vector2** m_texCoords;
		Liar::Uint m_numberTexCoodrs;

	protected:
		virtual void Destroy()
		{
			size_t i = 0;
			for (i = 0; i < m_numberPostions; ++i)
			{
				m_positons[i]->~Vector3();
				m_positons[i] = nullptr;
			}

			if (m_positons) free(m_positons);
			m_positons = nullptr;

			for (i = 0; i < m_numberNormals; ++i)
			{
				m_normals[i]->~Vector3();
				m_normals[i] = nullptr;
			}
			if (m_normals) free(m_normals);
			m_normals = nullptr;

			for (i = 0; i < m_numberTexCoodrs; ++i)
			{
				m_normals[i]->~Vector3();
				m_normals[i] = nullptr;
			}
			if (m_texCoords) free(m_texCoords);
			m_texCoords = nullptr;
		}

	protected:
		void AddPositonVertex(Liar::Number x, Liar::Number y, Liar::Number z)
		{
			void* buffer = GetVertexBuffer(Liar::VertexElementAttr::POSITION, (void**)m_positons, m_numberPostions, x, y, z);
			Liar::Vector3* positon = static_cast<Liar::Vector3*>(buffer);
			if (!positon)
			{
				++m_numberPostions;
				if (!m_positons) m_positons = (Liar::Vector3**)malloc(sizeof(Liar::Vector3*));
				else m_positons = (Liar::Vector3**)realloc(m_positons, sizeof(Liar::Vector3*)*m_numberPostions);
				m_positons[m_numberPostions - 1]->Set(x, y, z);
			}
		};

		void AddNormalVertex(Liar::Number x, Liar::Number y, Liar::Number z)
		{
			void* buffer = GetVertexBuffer(Liar::VertexElementAttr::NORMAL, (void**)m_normals, m_numberNormals, x, y, z);
			Liar::Vector3* normal = static_cast<Liar::Vector3*>(buffer);
			if (!normal)
			{
				++m_numberNormals;
				if (!m_normals) m_normals = (Liar::Vector3**)malloc(sizeof(Liar::Vector3*));
				else m_normals = (Liar::Vector3**)realloc(m_normals, sizeof(Liar::Vector3*)*m_numberNormals);
				m_normals[m_numberNormals - 1]->Set(x, y, z);
			}
		};

		void AddTexCoordVertex(Liar::Number x, Liar::Number y)
		{
			void* buffer = GetVertexBuffer(Liar::VertexElementAttr::TEXTURECOORDINATE, (void**)m_texCoords, m_numberTexCoodrs, x, y);
			Liar::Vector2* texCoord = static_cast<Liar::Vector2*>(buffer);
			if (!texCoord)
			{
				++m_numberTexCoodrs;
				if (!m_texCoords) m_texCoords = (Liar::Vector2**)malloc(sizeof(Liar::Vector2*));
				else m_texCoords = (Liar::Vector2**)realloc(m_texCoords, sizeof(Liar::Vector2*)*m_numberTexCoodrs);
				m_texCoords[m_numberTexCoodrs - 1]->Set(x, y);
			}
		};

	public:
		virtual void AddSubVertexBuffer(Liar::VertexElementAttr attr, Liar::Number x, Liar::Number y, Liar::Number z, Liar::Number)
		{
			switch (attr)
			{
			case Liar::VertexElementAttr::POSITION:
				AddPositonVertex(x, y, z);
				break;
			case Liar::VertexElementAttr::NORMAL:
				AddNormalVertex(x, y, z);
				break;
			case Liar::VertexElementAttr::TEXTURECOORDINATE:
				AddTexCoordVertex(x, y);
				break;
			}
		}
	};
}