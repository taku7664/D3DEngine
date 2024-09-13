#include "pch.h"
#include "Entity.h"

void Engine::Entity::SetActive(bool _isActive)
{
	if (m_state == GameState::Active || m_state == GameState::Passive)
	{
		if (_isActive)
		{
			m_state = GameState::Active;
			OnEnable();
		}
		if (!_isActive)
		{
			m_state = GameState::Passive;
			OnDisable();
		}
	}
}

void Engine::Entity::SetDestroy()
{
	if (m_state != GameState::Create)
	{
		m_state = GameState::Destroy;
		OnDestroy();
	}
}