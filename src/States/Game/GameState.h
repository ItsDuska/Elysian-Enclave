#pragma once
#include "States/State/State.h"
#include "States/State/StateManager.h"
#include "SFML/Graphics.hpp"

//World core stuff guuuuh

#include "Core/world/WorldHandler.h"


//ECS
#include "Core/ECS/ECData/View.hpp"
#include "Core/ECS/Event.hpp"
#include "Core/ECS/System.hpp"



class GameWorldState : public State
{
public:
	GameWorldState(StateManager* manager, sf::Vector2f& windowSize);
	void update(const float deltaTime) override;
	void render(sf::RenderTarget& window) override;
	void wake() override;
	void handleEvent(sf::Event& event) override;

private:


private:
	sf::Vector2f windowSize;
	StateManager* stateManager;


	// GAME WORLD
	std::unique_ptr<TileWorldHandler> handler;

	// ECS STUFF // TODO: Siirrä muualle kai? //

	EntityManager entityManager;
	EventManager eventManager;
	SystemManager systems;

	
};