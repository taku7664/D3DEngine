#pragma once

namespace Engine
{
	class WindowContext;
	_INTERFACE ILifeCycle
	{
	public:
		virtual void FixedUpdate() = 0;
		virtual void PreUpdate() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void Render() = 0;
	};
}

