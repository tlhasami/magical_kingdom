#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Centered Sprite");

    sf::Texture texture;
    if (!texture.loadFromFile("images/block.png"))
        return -1;

    sf::Sprite sprite(texture);

    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
    sprite.setPosition(1000 / 2, 600 / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
