#pragma once
#include "Console.h"

namespace Engine
{
	class WindowManager;

	class ConsoleContext : public Console
	{
	public:
	protected:
	private:
		friend class ::WindowManager;
	};
}
