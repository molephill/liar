#pragma once

#include <LiarType.h>

namespace Liar
{
	class StageContext
	{
	public:
		StageContext():
			m_depthTest(true), m_depthMask(true),
			m_depthFunc(GL_LESS), m_blend(false),
			m_sFactor(GL_ONE), m_dFactor(GL_ZERO),
			m_cullFace(false), m_frontFace(GL_CCW)
		{};
		~StageContext() 
		{};

	private:
		GLboolean m_depthTest;
		GLboolean m_depthMask;
		GLuint m_depthFunc;
		GLboolean m_blend;
		GLuint m_sFactor;
		GLuint m_dFactor;
		GLboolean m_cullFace;
		GLuint m_frontFace;

	public:
		void SetDepthTest(GLboolean value)
		{
			if (value != m_depthTest)
			{
				m_depthTest = value;
				value ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
			}
		}

		void SetDepthMask(GLboolean value)
		{
			if (value != m_depthMask)
			{
				m_depthMask = value;
				glDepthMask(value);
			}
		}

		void SetDepthFunc(GLuint value)
		{
			if (m_depthFunc != value)
			{
				m_depthFunc = value;
				glDepthFunc(value);
			}
		}

		void SetBlend(GLboolean value)
		{
			if (value != m_blend)
			{
				m_blend = value;
				value ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
			}
		}

		void SetBlendFunc(GLuint sFactor, GLuint dFactor)
		{
			if (m_sFactor != sFactor || m_dFactor != dFactor)
			{
				m_sFactor = sFactor;
				m_dFactor = dFactor;
				glBlendFunc(m_sFactor, m_dFactor);
			}
		}

		void SetCullFace(GLboolean value)
		{
			if (m_cullFace != value)
			{
				m_cullFace = value;
				value ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
			}
		}

		void SetFrontFace(GLuint value)
		{
			if (m_frontFace != value)
			{
				m_frontFace = value;
				glFrontFace(m_frontFace);
			}
		}

		void TexParameteri(GLenum target, GLenum pname, const GLint params)
		{
			glTexParameteri(target, pname, params);
		};

		void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
		{
			glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
		}

		void GenerateMipmap(GLenum type)
		{
			glGenerateMipmap(type);
		}

		void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data)
		{
			glBufferSubData(target, offset, size, data);
		}

		void DeleteBuffers(GLsizei n, const GLuint* buffers)
		{
			glDeleteBuffers(n, buffers);
		}

		void GenVertexArrays(GLsizei n, GLuint *arrays)
		{
			glGenVertexArrays(n, arrays);
		}

		void BindVertexArray(GLuint array)
		{
			glBindVertexArray(array);
		}

		void GenBuffers(GLsizei n, GLuint *arrays)
		{
			glGenBuffers(n, arrays);
		}

		void BindBuffer(GLenum target, GLuint buffer)
		{
			glBindBuffer(target, buffer);
		}

		void BufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)
		{
			glBufferData(target, size, data, usage);
		}

		void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
		{
			glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		}

		void EnableVertexAttribArray(GLuint index)
		{
			glEnableVertexAttribArray(index);
		}

		void DrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices)
		{
			glDrawElements(mode, count, type, indices);
		}

		void Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
		{
			glViewport(x, y, width, height);
		}

		void Scissor(GLint x, GLint y, GLsizei width, GLsizei height)
		{
			glScissor(x, y, width, height);
		}

		void ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
		{
			glClearColor(red, green, blue, alpha);
		}

		void Clear(GLbitfield mask)
		{
			glClear(mask);
		}
	};
}