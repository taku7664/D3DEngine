#pragma once

class Window;
class WindowInfo;

namespace Renderer
{
	class IRenderer
	{
	public:
		virtual bool Initialize(Engine::WindowContext* _window) = 0;
		virtual void Release() = 0;
		virtual void Clear() = 0;
		virtual void Clear(ColorF _color) = 0;
		virtual void BeginRender() = 0;
		virtual void EndRender() = 0;
	};
}