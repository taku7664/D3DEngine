#pragma once
#include "DemoApplication.h"

class TestWorld_01 : public World
{
public:
	virtual void WorldLoad() override;
	virtual void WorldDestroy() override;
	virtual void WorldEnter() override;
	virtual void WorldExit() override;
};

