
#ifndef Stage_hpp
#define Stage_hpp

#include <LiarType.h>
#include <core/render/BaseCamera.h>
#include <core/display/Node.h>

namespace Liar
{

	class Stage:public Liar::Node
	{
	public:
		Stage(Liar::Int w, Liar::Int h);
		virtual ~Stage();

	private:
		Liar::Uint m_width;
		Liar::Uint m_height;
		Liar::BaseCamera** m_cameras;
		Liar::Uint m_numberCamera;

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
		bool OnEnterFrame(Liar::RenderState& state);

		virtual Liar::Int CollectRenderUint(Liar::RenderState&);
	};
}

#endif /* Stage_hpp */
