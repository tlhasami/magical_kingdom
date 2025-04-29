#include "button.h"

Font Button::font;

Button::Button(string str, Vector2f position, Color color, Color text_color ,int characterSize)
{
    // Make sure font is loaded before using this Button
    text.setString(str);
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setFillColor(text_color);

    rect.setSize(Vector2f(text.getGlobalBounds().width + 20, 50));
    rect.setFillColor(color);
    rect.setPosition(position);

    text.setPosition(position.x + (rect.getSize().x - text.getGlobalBounds().width) / 2, 
                     position.y + (rect.getSize().y - text.getGlobalBounds().height) / 2 - 15);
}

void Button::draw(RenderWindow &window)
{
    window.draw(rect);
    window.draw(text);
}

bool Button::isClicked(Vector2i mousePosition)
{
    return rect.getGlobalBounds().contains(static_cast<Vector2f>(mousePosition));
}

void Button::ChangeColor()
{
    if (rect.getFillColor() == Color::Blue)
    {
        rect.setFillColor(Color(255, 69, 0));
        text.setFillColor(Color::Black);
    }
    else
    {
        rect.setFillColor(Color::Blue);
        text.setFillColor(Color::Yellow);
    }
}

Color Button::getColor() const
{
    return rect.getFillColor();
}

void Button::setPosition(Vector2f position)
{
    rect.setPosition(position);
    text.setPosition(position.x + (rect.getSize().x - text.getGlobalBounds().width) / 2, 
                     position.y + (rect.getSize().y - text.getGlobalBounds().height) / 2 - 15);
}

void Button::setRandom()
{
    setPosition({static_cast<float>(rand() % int(screenResolution.x - rect.getSize().x)), 
                 static_cast<float>(rand() % int(screenResolution.y - rect.getSize().y))});
}


// Function to Display String On Screen on Runtime
void displayText(string text, Vector2f position, RenderWindow &window, int characterSize, Color color)
{

    // Initalize _text -> setFont -> setCharacterSize -> setFillColor -> setPosition
    Text textt;
    textt.setString(text);
    textt.setFont(Button::font);
    textt.setCharacterSize(characterSize);
    textt.setFillColor(color);
    textt.setPosition(position);

    // Render On Screen
    window.draw(textt);
}