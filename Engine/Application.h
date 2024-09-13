#pragma once
#include "pch.h"
#include "Core/ProcessCore.h"

namespace Engine
{
	_ABSTRACT Application
	{
	public:
		static Application* Instance;

		Application() = delete;
		Application(HINSTANCE _hInstance);
		virtual ~Application();

		virtual void Initialize() = 0;
		virtual void Run() final;
		virtual void Release() final;

	protected:
		ProcessCore* processCore;
	private:
		static HINSTANCE m_hInstance;
		static bool m_isQuit;
	public:
		static void Quit() { m_isQuit = true; }

		operator HINSTANCE()
		{
			return this->m_hInstance;
		}
	};
}