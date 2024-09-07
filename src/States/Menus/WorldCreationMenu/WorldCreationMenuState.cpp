#include "WorldCreationMenuState.h"

WorldCreationMenuState::WorldCreationMenuState(std::shared_ptr<MenuContext>& menuContext)
	: context(menuContext), ui(10u)
{
	//const unsigned int NORMAL_FONT_SIZE = 50u;
	//const float SCALE = std::min(context->windowSize.x, context->windowSize.y) / 800.0f;

	//const unsigned int fontSize = static_cast<unsigned int>(NORMAL_FONT_SIZE * SCALE);

	//sf::Color color(34u, 38u, 65u, 76u);

	
	renderTexture.create(static_cast<unsigned int>(context->windowSize.x), static_cast<unsigned int>(context->windowSize.y));
	renderAlpha = sf::Color(255, 255, 255, 255);
}

void WorldCreationMenuState::update(const float deltaTime)
{
	const float timePassed = context->clock.getElapsedTime().asSeconds();
	context->backgroundShader.setUniform("u_time", timePassed);

	//ui.update();
}

void WorldCreationMenuState::render(sf::RenderTarget& window)
{
	renderTexture.clear(sf::Color::Transparent);

	window.draw(context->backgroundRect, &context->backgroundShader);

	//ui.render(renderTexture);
	renderTexture.display();

	sf::Sprite renderWindow(renderTexture.getTexture());
	renderWindow.setColor(renderAlpha);

	window.draw(renderWindow);
}

void WorldCreationMenuState::wake()
{
}

void WorldCreationMenuState::handleEvent(sf::Event& event)
{
	ui.handleEvent(event);
}
