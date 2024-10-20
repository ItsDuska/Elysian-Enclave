#pragma once
#include "Core/ECS/System.hpp"

class EntityManager;

namespace EntityComponent
{
	struct Animation;
	struct Image;
}

class AnimationSystem : public System<AnimationSystem>
{
public:
	AnimationSystem();
	void update(EntityManager& entities, EventManager& events, float dt);
private:
	void changeSpriteFrame(EntityComponent::Image* image, EntityComponent::Animation* animation);
};
