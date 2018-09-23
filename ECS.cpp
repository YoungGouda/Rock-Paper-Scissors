#include "stdafx.h"
#include "ECS.h"
#include "Components.h"

void Entity::addGroup(Group mGroup)
{
	groupBitSet[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}