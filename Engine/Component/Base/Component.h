#pragma once

class Object;

_ABSTRACT Component : public Engine::ILifeCycle
{
public:
	Component(Object* _owner) : gameObject(_owner) { Start(); }
	virtual ~Component() {}

	virtual void Start() {};

	Object* const gameObject;
protected:
};

