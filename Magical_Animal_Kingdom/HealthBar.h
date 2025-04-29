#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class HealthBar
{
private:
    RectangleShape background;
    RectangleShape bar;
    Vector2f position;
    float maxWidth;

public:
    HealthBar(Vector2f pos, Vector2f size);

    void update(int currentHealth, int maxHealth);
    void draw(RenderWindow& window);
    void setPosition(Vector2f pos);
};
