#pragma once

namespace Engine
{
	_ABSTRACT Entity
	{
	public:
		void SetName(std::wstring_view _name) { m_name = _name; }
		void SetTag(std::wstring_view _tag) { m_tag = _tag; }
		void SetActive(bool _isActive);
		void SetDestroy();

		const std::wstring& GetName() { return m_name; }
		const std::wstring& GetTag() { return m_name; }
		const GameState GetState() { return m_state; }
	protected:
		std::wstring m_name;
		std::wstring m_tag;
		GameState	 m_state;

		Entity() : m_name(L""), m_tag(L""), m_state(GameState::Create) { OnCreate(); }
		Entity(std::wstring_view _name, std::wstring_view _tag)
			: m_name(_name), m_tag(_tag), m_state(GameState::Create) { OnCreate(); }
	protected:
		virtual _CALLBACK OnEnable() {}
		virtual _CALLBACK OnDisable() {}
		virtual _CALLBACK OnCreate() {}
		virtual _CALLBACK OnDestroy() {}
	};
}