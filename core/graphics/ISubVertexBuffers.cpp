#include <core/graphics/ISubVertexBuffers.h>

namespace Liar
{
	void* ISubVertexBuffers::GetSubVertexBuffer(Liar::VertexFormatType type, void** buffers, size_t len, void* tmp)
	{
		for (size_t i = 0; i < len; ++i)
		{
			void* buffer = buffers[i];
			switch (type)
			{
			case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR3:
			{
				Liar::Vector3* tmpVec0 = static_cast<Liar::Vector3*>(buffer);
				if (tmpVec0)
				{
					Liar::Vector3* tmpVec1 = static_cast<Liar::Vector3*>(tmp);
					if(tmpVec1 && tmpVec0->Equal(*tmpVec1)) return buffer;
				}
				break;
			}
			case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR2:
			{
				Liar::Vector2* tmpVec0 = static_cast<Liar::Vector2*>(buffer);
				if (tmpVec0)
				{
					Liar::Vector2* tmpVec1 = static_cast<Liar::Vector2*>(tmp);
					if (tmpVec1 && tmpVec0->Equal(*tmpVec1)) return buffer;
				}
				break;
			}
			case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_VECTOR4:
			{
				Liar::Vector4* tmpVec0 = static_cast<Liar::Vector4*>(buffer);
				if (tmpVec0)
				{
					Liar::Vector4* tmpVec1 = static_cast<Liar::Vector4*>(tmp);
					if (tmpVec1 && tmpVec0->Equal(*tmpVec1)) return buffer;
				}
				break;
			}
			case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_QUATERNION:
			{
				Liar::Quaternion* tmpVec0 = static_cast<Liar::Quaternion*>(buffer);
				if (tmpVec0)
				{
					Liar::Quaternion* tmpVec1 = static_cast<Liar::Quaternion*>(tmp);
					if (tmpVec1 && tmpVec0->Equal(*tmpVec1)) return buffer;
				}
				break;
			}
			case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_INT:
			{
				Liar::IntHeapOperator* tmpVec0 = static_cast<Liar::IntHeapOperator*>(buffer);
				if (tmpVec0)
				{
					Liar::IntHeapOperator* tmpVec1 = static_cast<Liar::IntHeapOperator*>(tmp);
					if (tmpVec1 && tmpVec0->Equal(*tmpVec1)) return buffer;
				}
				break;
			}
			case Liar::VertexFormatType::VERTEX_FORMAT_TYPE_FLOAT:
			{
				Liar::FloatHeapOperator* tmpVec0 = static_cast<Liar::FloatHeapOperator*>(buffer);
				if (tmpVec0)
				{
					Liar::FloatHeapOperator* tmpVec1 = static_cast<Liar::FloatHeapOperator*>(tmp);
					if (tmpVec1 && tmpVec0->Equal(*tmpVec1)) return buffer;
				}
				break;
			}
			}
		}

		return nullptr;
	}

	size_t ISubVertexBuffers::UploadData(Liar::StageContext& gl, GLenum type, size_t offset, void* data)
	{
		size_t size = GetSize();
		gl.BufferSubData(type, offset, size, data);
		return offset + size;
	}

	size_t ISubVertexBuffers::AttribPointer(Liar::VertexAttribPointer index, Liar::StageContext& gl, size_t stride, size_t offset)
	{
		gl.VertexAttribPointer(index, GetFormat(), GetType(), GL_FALSE, stride, (void*)offset);
		gl.EnableVertexAttribArray(index);
		return offset + GetSize();
	}
}
