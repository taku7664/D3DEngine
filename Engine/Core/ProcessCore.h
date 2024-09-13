#pragma once
#include "Window/Window/WindowContext.h"
#include "Window/Console/ConsoleContext.h"
#include "Core/WorldCore.h"
#include "Core\WindowCore.h"

class Window;
class WindowData;

namespace Engine
{
	class WindowContext;
	
	class ProcessCore final
		: public ILifeCycle
	{
	public:
		ProcessCore();
		~ProcessCore();

		void Run();
		void Release();

		virtual void FixedUpdate() override;
		virtual void PreUpdate() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:
		WorldCore* m_worldCore;
		WindowCore* m_windowManager;
	public:
	};
}