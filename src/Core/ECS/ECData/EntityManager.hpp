#pragma once
#include "Defines.hpp"
#include <vector>


EntityID CreateEntityId(EntityIndex index, EntityVersion version);
EntityIndex GetEntityIndex(EntityID id);
EntityVersion GetEntityVersion(EntityID id);
bool IsEntityValid(EntityID id);

#define INVALID_ENTITY CreateEntityId(EntityIndex(-1), 0)


class ComponentPool
{
public:
	ComponentPool();
	ComponentPool(size_t elementsize);
	//~ComponentPool();
	void clean();
	void* get(size_t index);
	bool isNull();
private:
	char* data;
	size_t elementSize;
};


class EntityManager
{
public:
	EntityID newEnity();

	template<typename Component>
	Component* addComponent(EntityID id)
	{
		const EntityIndex index = GetEntityIndex(id);
		const int componentID = util::generateNewID<Component>();

		if (componentPools.size() <= componentID)
		{
			componentPools.resize(componentID + 1);
		}

		if (componentPools[componentID].isNull())
		{
			ComponentPool newPool(sizeof(Component));
			componentPools[componentID] = std::move(newPool);
		}

		//Position* component = static_cast<Position*>(componentPools[componentID].get(index));
		Component* component = new (componentPools[componentID].get(index)) Component();
		entities[index].mask.set(componentID);
		return component;
	}

	template<typename Component>
	void removeComponent(EntityID id);

	template<typename Component>
	Component* getComponentPtr(EntityID id)
	{
		const EntityIndex index = GetEntityIndex(id);
		const int componentID = util::generateNewID<Component>();
		if (!entities[index].mask.test(componentID))
		{
			return nullptr;
		}

		return static_cast<Component*>(componentPools[componentID].get(index));
	}

	void removeEntity(EntityID id);
	
	~EntityManager();

private:
	friend class Iterator;

	template<typename... ComponentTypes>
	friend struct View;

	struct EntityInfo
	{
		EntityID id;
		ComponentMask mask;
	};

	std::vector<EntityInfo> entities;
	std::vector<EntityIndex> freeEntities;
	std::vector<ComponentPool> componentPools;
};



