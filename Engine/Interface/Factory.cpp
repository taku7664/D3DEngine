#include "pch.h"
#include "Factory.h"

void Engine::Factory::CreateUpdate()
{
	for (auto instance : m_watingCreations)
	{
		instance->SetActive(true);
	}
	m_watingCreations.clear();
}

void Engine::Factory::DestroyUpdate()
{
	for (auto instance : m_watingDestructions)
	{
		SAFE_DELETE(instance);
	}
}
