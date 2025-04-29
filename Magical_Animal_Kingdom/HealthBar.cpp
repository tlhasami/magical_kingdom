#include "HealthBar.h"

HealthBar::HealthBar(Vector2f pos, Vector2f size)
    : position(pos), maxWidth(size.x)
{
    background.setSize(size);
    background.setFillColor(Color::Red);
    background.setPosition(pos);

    bar.setSize(size);
    bar.setFillColor(Color::Green);
    bar.setPosition(pos);
}

void HealthBar::update(int currentHealth, int maxHealth)
{
    float healthPercent = static_cast<float>(currentHealth) / maxHealth;
    bar.setSize(Vector2f(maxWidth * healthPercent, bar.getSize().y));
}

void HealthBar::draw(RenderWindow& window)
{
    
    window.draw(background);
    window.draw(bar);
}

void HealthBar::setPosition(Vector2f pos)
{
    position = pos;
    background.setPosition(pos);
    bar.setPosition(pos);
}
