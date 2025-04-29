#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

class Object
{
public:
    Texture texture;
    Sprite sprite;

    Object(string path, Vector2f position, Vector2f scale);

    void draw(RenderWindow &window);
    void changePosition(Vector2f newPosition);
    void changeScale(Vector2f newScale);
    bool checkCollision(Vector2i mousePosition);
    FloatRect getGlobalBond() const;

    void moveObject(Vector2f velocity, float deltaTime, Vector2f windowSize);
    void setIntRect(float left, float top, float width, float height);

    float getHeight() const;
    float getLeft() const;
    float getRight() const;
    float getTop() const;
    float getBottom() const;
    float getWidth() const;

    void changeImage(string newPath);
};
