#include <component/Component3D.h>

namespace Liar
{
	Component3D::Component3D():
		Liar::EventDispatcher(),
		Liar::IUpdate()
	{
	}


	Component3D::~Component3D()
	{
	}
}
