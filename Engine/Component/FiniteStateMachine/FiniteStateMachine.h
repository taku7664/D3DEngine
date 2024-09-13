#pragma once
#include "Component/Base/MonoBehaviour.h"
#include "Component/Base/Component.h"

class FiniteStateMachine
	: public Engine::MonoBehaviour
	, public Component
{
public:
	FiniteStateMachine(Object* _owner) : Component(_owner) {}
	virtual ~FiniteStateMachine();
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void PreUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
private:
};

