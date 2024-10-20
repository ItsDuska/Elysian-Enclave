#pragma once
#include <stdint.h>
#include <vector>
#include <unordered_map>
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
		enum class Direction
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

		EntityStates currentState;
		EntityStates possibleState;
		Direction facing;
	};


	// // TEMP COMPONENT //
	// REMOVE WHEN BATCHING SUPPORT IS ADDED
	struct Image
	{
		sf::Sprite sprite;
	};

	struct Animation
	{
		struct AnimationArray
		{
			struct AnimationFrame
			{
				sf::Vector2<uint16_t> texCoord;
			};

			enum AnimationType : uint16_t
			{
				WALK_DOWN = 0,
				WALK_RIGHT,
				WALK_LEFT,
				WALK_UP,

				TURN_DOWN_TO_LEFT,
				TURN_LEFT_TO_DOWN,
				TURN_DOWN_TO_RIGHT,
				TURN_RIGHT_TO_DOWN,
				TURN_UP_TO_LEFT,
				TURN_LEFT_TO_UP,
				TURN_UP_TO_RIGHT,
				TURN_RIGHT_TO_UP,

				WALK_BACKWARDS_FACING_DOWN,
				WALK_BACKWARDS_FACING_UP,
				WALK_BACKWARDS_FACING_LEFT,
				WALK_BACKWARDS_FACING_RIGHT,

				FALLING_FROM_DOWN,
				FALLING_FROM_UP,
				FALLING_FROM_LEFT,
				FALLING_FROM_RIGHT,

				IDLE_FROM_UP,
				IDLE_FROM_DOWN,
				IDLE_FROM_LEFT,
				IDLE_FROM_RIGHT,

				RUN, // EHKÄ EI
				ATTACK,
				// TODO: ADD MORE ANIMATION TYPES TO HERE.
			};
			uint16_t duration; //Milli seconds? maybe guh //maybe a float here?
			uint16_t animationType;
			std::vector<AnimationFrame> frames;
			bool loop;


			static bool isTurnAnimation(uint16_t animation)
			{
				return (animation >= TURN_DOWN_TO_LEFT && animation <= TURN_RIGHT_TO_UP);
			}

			static bool isFallingAnimation(uint16_t animation)
			{
				return (animation >= FALLING_FROM_UP && animation <= FALLING_FROM_RIGHT);
			}
		};

		std::unordered_map<uint16_t, AnimationArray> animations;
		sf::Vector2i spriteSize;
		uint16_t currentAnimation;
		int currentFrameIndex;                      
		float timeAccumulator;                        
		bool isPlaying;

		void setAnimation(int animationType) // enum thingy duh...
		{
			if (currentAnimation == animationType)
			{
				return;
			}

			if (animations.find(animationType) != animations.end())
			{
				currentAnimation = animationType;
				currentFrameIndex = 0;
				timeAccumulator = 0;
				isPlaying = true;
			}
		}

		const AnimationArray::AnimationFrame& getCurrentFrame() const
		{
			return animations.at(currentAnimation).frames[currentFrameIndex];
		}
	};

}