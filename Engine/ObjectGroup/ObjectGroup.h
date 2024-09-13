#pragma once
#include "Object/Object.h"

class ObjectGroup final
	: public Engine::Entity
	, public Engine::ILifeCycle
	, public Engine::Factory
{
public:
	ObjectGroup(std::wstring_view _name, std::wstring_view _tag);
	virtual ~ObjectGroup();

	virtual void FixedUpdate() override;
	virtual void PreUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
private:
	// list를 쓸지 vector를 쓸지 개큰고민중
	std::vector<Object*> m_objects;
public:
	//============ObjectGroup메소드============
	template <class T>
	T* CreateObject(std::wstring_view _name, std::wstring_view _tag);
	void TakeObjectToThis(Object* _dest) {}
};

template <class T>
T* ObjectGroup::CreateObject(std::wstring_view _name, std::wstring_view _tag)
{
	T* object = Create<T>(_name, _tag, this);
	m_objects.push_back(object);
	return object;
}