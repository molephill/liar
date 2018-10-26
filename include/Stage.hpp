
#ifndef Stage_hpp
#define Stage_hpp

#include "OpenGLWindow.hpp"

namespace Liar
{
	static const float WINDOW_W = 960;
	static const float WINDOW_H = 600;

	class Stage
	{
	public:
		Stage(Liar::uint w = WINDOW_W, Liar::uint h = WINDOW_H);
		~Stage();

	private:
		Liar::uint m_width;
		Liar::uint m_height;
		float m_red;
		float m_green;
		float m_blue;
        bool m_isActive;
		OpenGLWindow* m_openglMainWindow;

	public:
		bool Run();
		Liar::uint GetWidth() const { return m_width; };
		Liar::uint GetHeight() const { return m_height; };
		
		void SetSize(Liar::uint, Liar::uint);
	};
}

#endif /* Stage_hpp */
