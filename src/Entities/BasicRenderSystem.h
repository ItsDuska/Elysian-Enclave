#pragma once
#include "Core/ECS/System.hpp"


class EntityManager;
namespace sf
{
	class RenderTarget;
}


class BasicRenderSystem : public System<BasicRenderSystem>
{
public:
	BasicRenderSystem(sf::RenderTarget* target);
	void update(EntityManager& entities, EventManager& events, float dt);
	void render(EntityManager& entities);

private:
	sf::RenderTarget *target;
};