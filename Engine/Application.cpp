#include "pch.h"
#include "Application.h"

namespace Engine
{
	Application*  Application::Instance = nullptr;
	bool		  Application::m_isQuit = false;
	HINSTANCE	  Application::m_hInstance = nullptr;

	Application::Application(HINSTANCE _hInstance)
	{
		Instance = this;
		m_hInstance = _hInstance;

		processCore = new ProcessCore();

		Time::Initialize();
		Input::Initialize();
	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		while (!Instance->m_isQuit)
		{
			Instance->processCore->Run();
		}
	}

	void Application::Release()
	{
		SAFE_RELEASE(Instance->processCore);
	}
}