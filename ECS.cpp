#include "stdafx.h"
#include "ECS.h"
#include "Components.h"

void Entity::add_group(const Group m_group)
{
	groupBitSet[m_group] = true;
	manager.add_to_group(this, m_group);
}