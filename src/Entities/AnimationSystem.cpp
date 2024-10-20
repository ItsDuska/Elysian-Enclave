#include "AnimationSystem.h"
#include "Core/ECS/ECData/EntityManager.hpp"
#include "Entities/BasicComponentData.h"
#include "Core/ECS/ECData/View.hpp"

AnimationSystem::AnimationSystem()
{
}


void AnimationSystem::update(EntityManager& entities, EventManager& events, float dt)
{
	for (EntityID entity : View<EntityComponent::Image, EntityComponent::Animation>(entities))
	{
		EntityComponent::Animation* animationComponent = entities.getComponentPtr<EntityComponent::Animation>(entity);

        if (!animationComponent->isPlaying)
        {
            continue;
        }

        EntityComponent::Animation::AnimationArray& animation = animationComponent->animations[animationComponent->currentAnimation];

        animationComponent->timeAccumulator += 12*dt;

        if (animationComponent->timeAccumulator < (float)animation.duration)
        {
            continue;
        }

        //reset timer and move to next frame
        animationComponent->timeAccumulator = 0; 
        animationComponent->currentFrameIndex++;

        EntityComponent::Image* image = entities.getComponentPtr<EntityComponent::Image>(entity);

        //check if we are at the end of the loop or if it even loops guh.
        if (animationComponent->currentFrameIndex >= animation.frames.size())
        {
            if (animation.loop)
            {
                animationComponent->currentFrameIndex = 0;
                changeSpriteFrame(image,animationComponent);
                continue;
            }

            animationComponent->isPlaying = false;
            animationComponent->currentFrameIndex = animation.frames.size() - 1;

        }

        changeSpriteFrame(image, animationComponent);
	}
}

void AnimationSystem::changeSpriteFrame(EntityComponent::Image* image, EntityComponent::Animation* animation)
{
    sf::Vector2<uint16_t> texCoord = animation->getCurrentFrame().texCoord;
    sf::IntRect rect(sf::Vector2i(texCoord.x, texCoord.y), animation->spriteSize);
    image->sprite.setTextureRect(rect);
}
