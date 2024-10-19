#pragma once
#include "Core/ECS/System.hpp"
#include "Entities/BasicComponentData.h"

class MovementSystem : public System<MovementSystem>
{
public:
	void update(EntityManager& entities, EventManager& events, float dt);
private:
	//const float GRAVITY = 0.5f;
	const float MAX_FALLING_VELOCITY = 10.0f;

	void acceleration(EntityComponent::RigidBody* rigidBody);
	void deceleration(EntityComponent::RigidBody* rigidBody);

	//void gravity(EntityComponent::RigidBody& rigidBody);
};