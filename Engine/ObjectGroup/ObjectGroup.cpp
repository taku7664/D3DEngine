#include "pch.h"
#include "ObjectGroup.h"

ObjectGroup::ObjectGroup(std::wstring_view _name, std::wstring_view _tag)
	: Engine::Entity(_name, _tag)
{
}

ObjectGroup::~ObjectGroup()
{
}

void ObjectGroup::FixedUpdate()
{
}

void ObjectGroup::PreUpdate()
{
}

void ObjectGroup::Update()
{
}

void ObjectGroup::LateUpdate()
{
}

void ObjectGroup::Render()
{
}
