#include "PlayerInput.h"
#include "Core/ECS/ECData/EntityManager.hpp"
#include "Entities/BasicComponentData.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>


void PlayerInput::updatePlayerInput(EntityManager& entities, float dt)
{
	EntityComponent::RigidBody *rigidBody = entities.getComponentPtr<EntityComponent::RigidBody>(EntityComponent::PLAYER_ID);
	EntityComponent::Transform *transform = entities.getComponentPtr<EntityComponent::Transform>(EntityComponent::PLAYER_ID);
	EntityComponent::State* state = entities.getComponentPtr<EntityComponent::State>(EntityComponent::PLAYER_ID);
	EntityComponent::Speed* speed = entities.getComponentPtr<EntityComponent::Speed>(EntityComponent::PLAYER_ID);

	bool keyPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		state->facingLeft = false;
		keyPressed = true;
		rigidBody->direction.x = speed->speed;
		state->possibleState = EntityComponent::EntityStates::WALKING;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		state->facingLeft = true;
		keyPressed = true;
		rigidBody->direction.x = -speed->speed;
		state->possibleState = EntityComponent::EntityStates::WALKING;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && state->onGround)
	{
		keyPressed = true;
		state->onGround = false;
		rigidBody->velocity.y = -speed->jumpingSpeed;
		state->possibleState = EntityComponent::EntityStates::JUMP;
		state->triggerJump = true;
	}

	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		keyPressed = true;
		rigidBody->direction = { 0,0 };
		state->possibleState = EntityComponent::EntityStates::ATTACK;
	}

	else if (!keyPressed)
	{
		rigidBody->direction.x = 0;
		state->possibleState = EntityComponent::EntityStates::IDLE;
	}
}
