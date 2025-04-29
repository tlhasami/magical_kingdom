#include "object.h"

Object::Object(string path, Vector2f position, Vector2f scale)
{
    if (!texture.loadFromFile("images/" + path))
    {
        cout << "Error loading image Path : images/" << path << endl;
        exit(EXIT_FAILURE);
    }

    sprite.setTexture(texture);
    sprite.setScale(scale);
    sprite.setPosition(position);
}

void Object::draw(RenderWindow &window)
{
    window.draw(sprite);
}

void Object::changePosition(Vector2f newPosition)
{
    sprite.setPosition(newPosition);
}

void Object::changeScale(Vector2f newScale)
{
    sprite.setScale(newScale);
}

bool Object::checkCollision(Vector2i mousePosition)
{
    return sprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePosition));
}

FloatRect Object::getGlobalBond() const
{
    return sprite.getGlobalBounds();
}

void Object::moveObject(Vector2f velocity, float deltaTime, Vector2f windowSize)
{
    sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);

    if (sprite.getPosition().x < 0)
    {
        sprite.setPosition(0, sprite.getPosition().y);
    }
    else if (sprite.getPosition().x + sprite.getGlobalBounds().width > windowSize.x)
    {
        sprite.setPosition(windowSize.x - sprite.getGlobalBounds().width, sprite.getPosition().y);
    }

    if (sprite.getPosition().y < 0)
    {
        sprite.setPosition(sprite.getPosition().x, 0);
    }
    else if (sprite.getPosition().y + sprite.getGlobalBounds().height > windowSize.y)
    {
        sprite.setPosition(sprite.getPosition().x, windowSize.y - sprite.getGlobalBounds().height);
    }
}

void Object::setIntRect(float left, float top, float width, float height)
{
    sprite.setTextureRect(IntRect(left, top, width, height));
}

float Object::getHeight() const
{
    return sprite.getGlobalBounds().height;
}

float Object::getLeft() const
{
    return sprite.getGlobalBounds().left;
}

float Object::getRight() const
{
    return sprite.getGlobalBounds().left + sprite.getGlobalBounds().width;
}

float Object::getTop() const
{
    return sprite.getGlobalBounds().top;
}

float Object::getBottom() const
{
    return sprite.getGlobalBounds().top + sprite.getGlobalBounds().height;
}

float Object::getWidth() const
{
    return sprite.getGlobalBounds().width;
}

void Object::changeImage(string newPath)
{
    if (!texture.loadFromFile("images/" + newPath))
    {
        cout << "Error loading image Path : images/" << newPath << endl;
        exit(EXIT_FAILURE);
    }
    sprite.setTexture(texture);
}
