#include "BasicRenderSystem.h"
#include "Core/ECS/ECData/EntityManager.hpp"
#include "Entities/BasicComponentData.h"
#include <SFML/Graphics.hpp>
#include "Core/ECS/ECData/View.hpp"
#include <iostream>


BasicRenderSystem::BasicRenderSystem(sf::RenderTarget* target)
{
	this->target = target;
}

void BasicRenderSystem::update(EntityManager& entities, EventManager& events, float dt)
{
}

void BasicRenderSystem::render(EntityManager& entities)
{
	//EntityComponent::Transform* transform = entities.getComponentPtr<EntityComponent::Transform>();
	for (EntityID entity : View<EntityComponent::Image, EntityComponent::Transform>(entities))
	{
		EntityComponent::Transform* transform = entities.getComponentPtr<EntityComponent::Transform>(entity);
		EntityComponent::Image* image = entities.getComponentPtr<EntityComponent::Image>(entity);

		transform->position = transform->futurePosition;

		image->sprite.setPosition(transform->position);


		target->draw(image->sprite);
		std::cout << transform->position.x << "x " << transform->position.y << "\n";
	}
}
