#include "System.hpp"


uint32_t BaseSystem::counter = 0u;

SystemManager::SystemManager(EntityManager& entities, EventManager& events)
	: entities(entities), events(events)
{
}

void SystemManager::updateSystems(float dt)
{
	for (auto& pair : systems)
	{
		pair.second->update(entities, events, dt);
	}
}

void SystemManager::lateUpdateSystems()
{
	for (auto& pair : systems)
	{
		pair.second->render(entities);
	}
}

void SystemManager::wake()
{
	for (auto& pair : systems)
	{
		pair.second->wake(events);
	}
}

void BaseSystem::wake(EventManager& events)
{
}
