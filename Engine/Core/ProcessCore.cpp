#include "pch.h"
#include "ProcessCore.h"

namespace Engine
{
	ProcessCore::ProcessCore()
	{
		m_worldCore = new WorldCore();
		m_windowManager = new WindowCore();
		GameManager::world = m_worldCore;
		GameManager::window = m_windowManager;
	}
	ProcessCore::~ProcessCore()
	{
	}

	void ProcessCore::Run()
	{
		MSG msg;
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Time::Update();
			Input::Update();
			FixedUpdate();
			PreUpdate();
			Update();
			LateUpdate();
			Render();
			Input::Reset();
		}
	}

	void ProcessCore::Release()
	{
		SAFE_RELEASE(m_worldCore)
	}

	void ProcessCore::FixedUpdate()
	{
		static float fixedTick;
		fixedTick += Time::GetUnScaledDeltaTime();
		while (fixedTick)
		{
			m_worldCore->FixedUpdate();
			fixedTick -= GameManager::fixedTick;
		}
	}

	void ProcessCore::PreUpdate()
	{
		m_worldCore->PreUpdate();
	}

	void ProcessCore::Update()
	{
		m_worldCore->Update();
	}

	void ProcessCore::LateUpdate()
	{
		m_worldCore->LateUpdate();
	}

	void ProcessCore::Render()
	{
		m_worldCore->Render();
	}
}

