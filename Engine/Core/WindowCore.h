#pragma once
#include "Manager\WindowManager.h"

namespace Engine
{
	class WindowCore : public ::WindowManager
	{
	public:
		void BeginRender();
		void EndRender();

	};
}


