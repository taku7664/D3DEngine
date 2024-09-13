#pragma once
#include "Manager/WorldManager.h"

namespace Engine
{
	class WorldCore final
		: public WorldManager
		, public ILifeCycle
	{
	public:
		WorldCore() = default;
		~WorldCore() = default;
		void Release();
		virtual void FixedUpdate() override;
		virtual void PreUpdate() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:
	};
}