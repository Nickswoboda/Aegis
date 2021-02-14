#include "Widget.h"
#include "../Application.h"

namespace Aegis {

	Widget::Widget(AABB rect)
		:Object(), rect_(rect), font_(Application::GetFont())
	{}
}
