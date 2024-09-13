#pragma once
#include "Component/Base/MonoBehaviour.h"
#include "Component/Base/Component.h"

class Script
	: public Engine::MonoBehaviour
	, public Component
{
public:
	Script(Object* _owner) : Component(_owner) {}

	static ComponentType GetComponentType() { return ComponentType::Script; }
};

