#pragma once
#include <stdint.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace EntityComponent
{
	constexpr uint64_t PLAYER_ID = 0;

	struct Health
	{
		uint16_t maxHealt;
		uint16_t currentHealt;
		uint16_t healtRegen;
	};

	struct RigidBody
	{
		float maxVelocity;
		float acceleration;
		float deceleration;
		sf::Vector2f velocity;
		sf::Vector2f direction;
	};

	struct Transform
	{
		sf::Vector2f futurePosition;
		sf::Vector2f position;
	};

	struct Speed
	{
		float speed;
		float jumpingSpeed;
	};


	enum class EntityStates : uint8_t
	{
		WALKING,
		IDLE,
		JUMP,
		FALLING,
		ATTACK,
		TAKE_DAMAGE,
		DEATH
	};

	struct State
	{
		EntityStates currentState;
		EntityStates possibleState;
		bool triggerJump;
		bool facingLeft;
		bool onGround;
	};


	// // TEMP COMPONENT //
	// REMOVE WHEN BATCHING SUPPORT IS ADDED
	struct Image
	{
		sf::Sprite sprite;
	};

}