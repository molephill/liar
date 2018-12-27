#pragma once

#include <core/models/Mesh.h>

namespace Liar
{
	class Model:public Liar::Node
	{
	public:
		Model();
		~Model();

	protected:
		std::string m_url;

	protected:
		void RemoveAllMeshs();

	public:
		void SetURL(const char*);
		virtual Liar::Int CollectRenderUint(Liar::RenderState&, bool buildShader = true);
	};
}