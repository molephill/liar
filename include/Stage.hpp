
#ifndef Stage_hpp
#define Stage_hpp

#include "OpenGLWindow.hpp"

namespace Liar
{
	static const Liar::Number WINDOW_W = 960;
	static const Liar::Number WINDOW_H = 600;

	class Stage
	{
	public:
		Stage(Liar::Uint w = WINDOW_W, Liar::Uint h = WINDOW_H);
		~Stage();

	private:
		Liar::Uint m_width;
		Liar::Uint m_height;
		Liar::Number m_red;
		Liar::Number m_green;
		Liar::Number m_blue;
        bool m_isActive;
		OpenGLWindow* m_openglMainWindow;

	public:
		bool Run();
		Liar::Uint GetWidth() const { return m_width; };
		Liar::Uint GetHeight() const { return m_height; };
		
		void SetSize(Liar::Uint, Liar::Uint);
	};
}

#endif /* Stage_hpp */
