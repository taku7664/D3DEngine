#include "pch.h"
#include "WorldCore.h"

namespace Engine
{
	void WorldCore::Release()
	{
	}
	void WorldCore::FixedUpdate()
	{
		if(m_curWorld) m_curWorld->FixedUpdate();
	}
	void WorldCore::PreUpdate()
	{
		if (m_curWorld) m_curWorld->PreUpdate();
	}
	void WorldCore::Update()
	{
		if (m_curWorld) m_curWorld->Update();
	}
	void WorldCore::LateUpdate()
	{
		if (m_curWorld) m_curWorld->LateUpdate();
	}
	void WorldCore::Render()
	{
		if (m_curWorld) m_curWorld->Render();
	}
}