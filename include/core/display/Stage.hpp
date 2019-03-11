
#ifndef Stage_hpp
#define Stage_hpp

#include <LiarType.h>
#include <core/render/BaseCamera.h>
#include <core/light/BaseLight.h>
#include <core/display/Node.h>

namespace Liar
{

	class Stage:public Liar::Node
	{
	public:
		Stage(Liar::Uint w, Liar::Uint h);
		virtual ~Stage();

	private:
		Liar::Uint m_width;
		Liar::Uint m_height;

		Liar::BaseCamera** m_cameras;
		Liar::Uint m_numberCamera;

		Liar::BaseLight** m_lights;
		Liar::Uint m_numberLight;

	public:
		Liar::Number mouseX;
		Liar::Number mouseY;
		Liar::Number scrollX;
		Liar::Number scrollY;

	public:
		Liar::Uint GetWidth() const { return m_width; };
		Liar::Uint GetHeight() const { return m_height; };
		
		void SetSize(Liar::Uint, Liar::Uint);

		Liar::BaseCamera* AddCamera(Liar::BaseCamera*);
		Liar::BaseLight* AddLight(Liar::BaseLight*);

		bool OnEnterFrame(Liar::RenderState& state);

		virtual Liar::Int CollectRenderUint(Liar::RenderState&);
		virtual Liar::ClassType GetNodeType() const { return Liar::ClassType::CLASS_NODE_TYPE_STAGE; };
	};
}

#endif /* Stage_hpp */
