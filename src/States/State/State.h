#pragma once


namespace sf
{
	class RenderTarget;
	class Event;
	//class Event;
}

class State
{
public:
	//virtual void handleInput(const sf::Event& event) = 0;
	virtual void update(const float deltaTime) = 0;
	virtual void render(sf::RenderTarget& window) = 0;
	virtual void wake() = 0;
	virtual void handleEvent(sf::Event& event) = 0;
//protected:
	//bool exitValue = false;
};
