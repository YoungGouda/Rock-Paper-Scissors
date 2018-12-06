#pragma once
#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID last_id = 0u;
	return last_id++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID type_id = getNewComponentTypeID();
	return type_id;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public: 
	Entity * entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	virtual ~Component() {}
};

class Entity
{
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

public: 
	Entity(Manager& mManager) : manager(mManager)
	{}
	void update()
	{
		for (auto& c : components) c->update();
	}
	void draw() 
	{
		for (auto& c : components) c->draw();
	}
	bool is_active() const { return active; }
	void destroy() { active = false; }

	bool has_group(const Group m_group)
	{
		return groupBitSet[m_group];
	}

	void add_group(Group m_group);
	void del_group(const Group m_group)
	{
		groupBitSet[m_group] = false;
	}

	template <typename T> bool has_component() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& add_component(TArgs&&... m_args)
	{
		T* c(new T(std::forward<TArgs>(m_args)...));
		c->entity = this;
		std::unique_ptr<Component> u_ptr{ c };
		components.emplace_back(std::move(u_ptr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& get_component() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>>entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
	void update() 
	{
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v), [i](Entity* m_entity)
			{
				return !m_entity->is_active() || !m_entity->has_group(i);
			}),
				std::end(v));
		}
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &m_entity)
		{
			return !m_entity->is_active();
		}),
			std::end(entities));
	}

	void add_to_group(Entity* m_entity, const Group m_group)
	{
		groupedEntities[m_group].emplace_back(m_entity);
	}

	std::vector<Entity*>& get_group(const Group m_group)
	{
		return groupedEntities[m_group];
	}

	Entity& add_entity()
	{
		const auto e = new Entity(*this);
		std::unique_ptr<Entity> u_ptr{ e };
		entities.emplace_back(std::move(u_ptr));
		return *e;
	}
};