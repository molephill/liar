
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
        
		bool m_isFirstMove;
		Liar::DNumber m_lastMouseX;
		Liar::DNumber m_lastMouseY;

	private:
		Liar::BaseCamera** m_cameras;
		Liar::Uint m_numberCamera;

	public:
		Liar::Uint GetWidth() const { return m_width; };
		Liar::Uint GetHeight() const { return m_height; };
		
		void SetSize(Liar::Uint, Liar::Uint);
		void MouseEvent(Liar::DNumber, Liar::DNumber, Liar::Int);
		void ScrollEvent(Liar::DNumber, Liar::DNumber);

		Liar::BaseCamera* AddCamera(Liar::BaseCamera*);
		bool OnEnterFrame(Liar::RenderState& state);
	};
}

#endif /* Stage_hpp */
