#pragma once
#include "Component/Script/Script.h"
class Component;
class ObjectGroup;

class Object
	: public Engine::Entity
	, public Engine::ILifeCycle
{
	using ComponentArray = std::array<std::vector<Component*>, static_cast<int>(ComponentType::SIZE)>;
public:
	Object(std::wstring_view _key, std::wstring_view _tag, ObjectGroup* _ownerObjectGroup);
	~Object();

	virtual void FixedUpdate();
	virtual void PreUpdate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
private:
	ObjectGroup*   m_ownerGroup;
	ComponentArray m_components;

	virtual _CALLBACK OnEnable() override;
	virtual _CALLBACK OnDisable() override;
	virtual _CALLBACK OnDestroy() override;
public:	//============Object¸Þ¼Òµå============
	ObjectGroup* GetObjectGroupOwner() { return m_ownerGroup; }
	template <class T, typename... Args>
	T* AddComponent(Args&&... args);
	template <class T>
	T* GetComponent(int _index = 0);
};

template <class T, typename... Args>
T* Object::AddComponent(Args&&... args)
{
	static_assert(std::is_base_of<Component, T>::value, "AddComponent_Fail");
	T* component = new T(this, std::forward<Args>(args)...);
	ComponentType type = T::GetComponentType();
	int index = static_cast<int>(type);
	m_components[index].push_back(component);
	return component;
}

template <class T>
T* Object::GetComponent(int _index)
{
	if (!m_components.empty())
	{
		ComponentType type = T::GetComponentType();
		int iType = static_cast<int>(type);
		if (_index >= m_components.size())
			_index = m_components.size() - 1;
		return m_components[iType][_index];
	}
	return nullptr;
}