
#ifndef Stage_hpp
#define Stage_hpp

#include <LiarType.h>
#include <core/display/Scene.h>

namespace Liar
{

	class Stage
	{
	public:
		Stage(Liar::Int w, Liar::Int h);
		~Stage();

	private:
		Liar::Uint m_width;
		Liar::Uint m_height;
		Liar::Number m_red;
		Liar::Number m_green;
		Liar::Number m_blue;
        
		bool m_isFirstMove;
		Liar::DNumber m_lastMouseX;
		Liar::DNumber m_lastMouseY;

	private:
		Liar::Scene** m_scenes;
		Liar::Uint m_numberChild;

	public:
		Liar::Uint GetWidth() const { return m_width; };
		Liar::Uint GetHeight() const { return m_height; };
		
		void SetSize(Liar::Uint, Liar::Uint);
		void MouseEvent(Liar::DNumber, Liar::DNumber, Liar::Int);
		void ScrollEvent(Liar::DNumber, Liar::DNumber);

		Liar::Node* AddChild(Liar::Node*);

		bool OnEnterFrame();
	};
}

#endif /* Stage_hpp */
