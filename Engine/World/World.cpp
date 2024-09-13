#include "pch.h"
#include "World.h"

std::vector<ObjectGroup*> World::m_globalGroups = {};

World::~World()
{
	for (ObjectGroup* layer : m_layers)
	{
		SAFE_DELETE(layer);
	}
}

void World::FixedUpdate()
{
	for (ObjectGroup* layer : m_layers)
	{
		if (layer->GetState() == GameState::Active)
			layer->FixedUpdate();
	}
}

void World::PreUpdate()
{
	CreateUpdate();
	for (ObjectGroup* layer : m_layers)
	{
		if (layer->GetState() == GameState::Active)
			layer->PreUpdate();
	}
}

void World::Update()
{
	for (ObjectGroup* layer : m_layers)
	{
		if (layer->GetState() == GameState::Active)
			layer->Update();
	}
}

void World::LateUpdate()
{
	for (ObjectGroup* layer : m_layers)
	{
		if (layer->GetState() == GameState::Active)
			layer->LateUpdate();
	}
}

void World::Render()
{
	for (auto iter = m_layers.begin(); iter != m_layers.end();)
	{
		if ((*iter)->GetState() == GameState::Destroy)
		{
			m_watingDestructions.push_back(*iter);
			iter = m_layers.erase(iter);
		}
		else
		{
			if ((*iter)->GetState() == GameState::Active)
				(*iter)->Render();
			++iter;
		}
	}
	DestroyUpdate();
}

ObjectGroup* World::CreateObjectGroup(std::wstring_view _name, std::wstring_view _tag)
{
	ObjectGroup* layer = Create<ObjectGroup>(_name, _tag);
	m_layers.push_back(layer);
	return layer;
}

ObjectGroup* World::operator[](std::wstring_view _key)
{
	for (ObjectGroup* layer : m_layers)
	{
		if (layer->GetName() == _key)
			return layer;
	}
	return nullptr;
}

