//
//  OpenGLWindow.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/19.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef OpenGLWindow_hpp
#define OpenGLWindow_hpp

#include <iostream>
#include "LiarType.h"

namespace Liar
{
	class Stage;

    class OpenGLWindow
    {
	public:
        OpenGLWindow(std::string title, Liar::Stage*);
		~OpenGLWindow();

	protected:
		Liar::Stage* m_renderStage;
		bool m_isFirstMove;
		double m_lastMouseX;
		double m_lastMouseY;

		void Run(GLFWwindow*, bool);

	public:
        void SetSize(GLFWwindow*, Liar::Uint, Liar::Uint);
        bool MouseEvent(GLFWwindow* window, double, double);
		void ScrollEvent(GLFWwindow* window, double, double);

	public:
		static Liar::OpenGLWindow* runWindow;
    };
}

#endif /* OpenGLWindow_hpp */
