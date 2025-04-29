#pragma once

#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

extern Vector2f screenResolution; // Declare screenResolution if it's used in setRandom()

class Button
{
public:
    RectangleShape rect;
    Text text;
    static Font font;

    Button(string str, Vector2f position, Color color = Color::Blue, Color text_color = Color::Yellow , int characterSize = 30);

    void draw(RenderWindow &window);
    bool isClicked(Vector2i mousePosition);
    void ChangeColor();
    Color getColor() const;
    void setPosition(Vector2f position);
    void setRandom();
    
};

// Function to Display String On Screen on Runtime
void displayText(string text, Vector2f position, RenderWindow &window, int characterSize, Color color);