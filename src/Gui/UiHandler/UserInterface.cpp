#include "UserInterface.h"


gui::UserInterface::UserInterface(const uint32_t maxWidgets)
    : eventInfo(), active(false), currentIndex(0u), keyNames({
        {sf::Keyboard::A, "A"},     {sf::Keyboard::B, "B"}, {sf::Keyboard::C, "C"},
        {sf::Keyboard::D, "D"},     {sf::Keyboard::E, "E"}, {sf::Keyboard::F, "F"},
        {sf::Keyboard::G, "G"},     {sf::Keyboard::H, "H"}, {sf::Keyboard::I, "I"},
        {sf::Keyboard::J, "J"},     {sf::Keyboard::K, "K"}, {sf::Keyboard::L, "L"},
        {sf::Keyboard::M, "M"},     {sf::Keyboard::N, "N"}, {sf::Keyboard::O, "O"},
        {sf::Keyboard::P, "P"},     {sf::Keyboard::Q, "Q"}, {sf::Keyboard::R, "R"},
        {sf::Keyboard::S, "S"},     {sf::Keyboard::T, "T"}, {sf::Keyboard::U, "U"},
        {sf::Keyboard::V, "V"},     {sf::Keyboard::W, "W"}, {sf::Keyboard::X, "X"},
        {sf::Keyboard::Y, "Y"},     {sf::Keyboard::Z, "Z"},

        {sf::Keyboard::Num0, "0"},  {sf::Keyboard::Num1, "1"}, {sf::Keyboard::Num2, "2"},
        {sf::Keyboard::Num3, "3"},  {sf::Keyboard::Num4, "4"}, {sf::Keyboard::Num5, "5"},
        {sf::Keyboard::Num6, "6"},  {sf::Keyboard::Num7, "7"}, {sf::Keyboard::Num8, "8"},
        {sf::Keyboard::Num9, "9"},

        {sf::Keyboard::Space, "Space"},         {sf::Keyboard::LControl, "Left Ctrl"},
        {sf::Keyboard::LShift, "Left Shift"},   {sf::Keyboard::RControl, "Right Ctrl"},
        {sf::Keyboard::RShift, "Right Shift"},  {sf::Keyboard::Tab, "Tab"},
        {sf::Keyboard::Escape, "Esc"},          {sf::Keyboard::Enter, "Enter"}
        })
{
    this->widgets.reserve(maxWidgets);
    clock.restart();
}

void gui::UserInterface::addWidget(std::unique_ptr<Widget> element)
{
    widgets.push_back(std::move(element));
}

void gui::UserInterface::update()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asSeconds() >= 0.2f)
    {
        eventInfo.mousePressed = !eventInfo.mousePressed;
        clock.restart();
    }

    for (unsigned int index = 0; index < widgets.size(); index++)
    {
        Widget* widget = widgets[index].get();

        if (widget->update(eventInfo))
        {
            active = true;
            currentIndex = index;
            break;
        }
    }
}

void gui::UserInterface::render(sf::RenderTarget& target)
{ 
    eventInfo.mousePosition = target.mapPixelToCoords(sf::Mouse::getPosition());
    
    for (const auto& widget : widgets)
    {
        widget->render(target);
    }
}

void gui::UserInterface::handleEvent(sf::Event& event)
{
    if (!active)
    {
        return;
    }

    const auto it = keyNames.find(event.key.code);

    switch (event.type)
    {
    case sf::Event::KeyPressed:
        eventInfo.key = event.key.code;

        if (it != keyNames.end())
        {
            eventInfo.textInput = it->second;
            eventInfo.keyPressed = true;
            active = false;
        }
        else
        {
            eventInfo.textInput = nullptr;
        }
        break;


    default:
        break;
    }
}

const sf::Keyboard::Key gui::UserInterface::getKey() const
{
    return eventInfo.key;
}

const char* gui::UserInterface::sfKeyToChar(sf::Keyboard::Key key)
{
    const auto it = keyNames.find(key);
    std::cout << it->second << "\n";
    return it->second;
}



