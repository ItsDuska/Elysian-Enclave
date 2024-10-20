#include "MovementSystem.h"
#include "Core/ECS/ECData/EntityManager.hpp"
#include "Core/ECS/ECData/View.hpp"

void MovementSystem::update(EntityManager& entities, EventManager& events, float dt)
{
	for (EntityID entity : View<EntityComponent::Transform, EntityComponent::RigidBody>(entities))
	{
		EntityComponent::Transform* transform = entities.getComponentPtr<EntityComponent::Transform>(entity);
		EntityComponent::RigidBody* body = entities.getComponentPtr<EntityComponent::RigidBody>(entity);
		acceleration(body);
		deceleration(body);

		transform->futurePosition = transform->position + body->velocity;
	}
}

void MovementSystem::acceleration(EntityComponent::RigidBody* rigidBody)
{
	// -- X DIRECTION --

	rigidBody->velocity.x += rigidBody->acceleration * rigidBody->direction.x;

	if (rigidBody->velocity.x > 0.f && rigidBody->velocity.x > rigidBody->maxVelocity)
	{
		rigidBody->velocity.x = rigidBody->maxVelocity;
	}

	else if (rigidBody->velocity.x < 0.f && rigidBody->velocity.x < -rigidBody->maxVelocity)
	{
		rigidBody->velocity.x = -rigidBody->maxVelocity;
	}

	// -- Y DIRECTION --

	rigidBody->velocity.y += rigidBody->acceleration * rigidBody->direction.y;

	if (rigidBody->velocity.y > 0.f && rigidBody->velocity.y > rigidBody->maxVelocity)
	{
		rigidBody->velocity.y = rigidBody->maxVelocity;
	}

	else if (rigidBody->velocity.y < 0.f && rigidBody->velocity.y < -rigidBody->maxVelocity)
	{
		rigidBody->velocity.y = -rigidBody->maxVelocity;
	}
}

void MovementSystem::deceleration(EntityComponent::RigidBody* rigidBody)
{
	// -- X DIRECTION --

	if (rigidBody->velocity.x > 0.f)
	{
		rigidBody->velocity.x -= rigidBody->deceleration;

		if (rigidBody->velocity.x < 0.f)
		{
			rigidBody->velocity.x = 0.f;
		}
	}

	else if (rigidBody->velocity.x < 0.f)
	{
		rigidBody->velocity.x += rigidBody->deceleration;

		if (rigidBody->velocity.x > 0.f)
		{
			rigidBody->velocity.x = 0.f;
		}
	}


	// -- Y DIRECTION --

	if (rigidBody->velocity.y > 0.f)
	{
		rigidBody->velocity.y -= rigidBody->deceleration;

		if (rigidBody->velocity.y < 0.f)
		{
			rigidBody->velocity.y = 0.f;
		}
	}

	else if (rigidBody->velocity.y < 0.f)
	{
		rigidBody->velocity.y += rigidBody->deceleration;

		if (rigidBody->velocity.y > 0.f)
		{
			rigidBody->velocity.y = 0.f;
		}
	}


}
