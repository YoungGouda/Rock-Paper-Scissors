#pragma once
#include "ECS.h"

class Command
{
public:
	virtual ~Command() = default;
	virtual void execute(Entity * entity) = 0;
	virtual void idle(Entity * entity) = 0;
};

