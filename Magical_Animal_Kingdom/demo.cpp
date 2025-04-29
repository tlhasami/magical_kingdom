#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"
#include "pets.h" // Include Pet header

using namespace sf;
using namespace std;

Vector2f screenResolution(1000, 600);

int main()
{
    cout << "Hello World" << endl;
    RenderWindow window(VideoMode(screenResolution.x, screenResolution.y), "Button and Griffin Example");
    window.setFramerateLimit(60);

    // Load the font for Button
    if (!Button::font.loadFromFile("fonts/Jersey.ttf"))
    {
        cout << "Error loading font!" << endl;
        return -1;
    }

    // Create a Button
    Button myButton("Click Me", {100, 100});

    // Create a Pets
    Griffin griffin("griffin.png",400,100 , 1.5f , 1.5f , 9);
    Dragon dragon("dragon.png", 300, 300, 1.5f, 1.5f, 8);
    Phoenix phoenix("phoniex.png" , 600 , 300 , .5f, .5f, 8 );
    Unicorn unicorn("unicorn.png" , 500 , 400 , 1.5f, 1.5f , 8);

    // Set initial frame of Pets
    dragon.setIntRect(0, 0, 75, 90);
    griffin.setIntRect(2, 0, 72, 90);
    phoenix.setIntRect(0, 50, 400, 200);
    unicorn.setIntRect(0, 121, 500/8 , 121 );

    Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                if (myButton.isClicked(mousePos))
                {
                    myButton.ChangeColor();
                    dragon.changePosition({
                        static_cast<float>(rand() % int(screenResolution.x - dragon.getWidth())),
                        static_cast<float>(rand() % int(screenResolution.y - dragon.getHeight()))
                    });
                    griffin.changePosition({
                        static_cast<float>(rand() % int(screenResolution.x - dragon.getWidth())),
                        static_cast<float>(rand() % int(screenResolution.y - dragon.getHeight()))
                    });
                }
            }
        }

        dragon.updateAnimation(deltaTime);
        griffin.updateAnimation(deltaTime);
        phoenix.updateAnimation(deltaTime);
        unicorn.updateAnimation(deltaTime);

        window.clear();
        myButton.draw(window);
        griffin.draw(window);
        dragon.draw(window);  
        phoenix.draw(window);
        unicorn.draw(window);
        window.display();
    }

    return 0;
}


/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"
#include "pets.h" // Include Pet header

using namespace sf;
using namespace std;

Vector2f screenResolution(1000, 600);

static void fontLoad()
{
    if (!Button::font.loadFromFile("fonts/Jersey.ttf"))
    {
        cout << "Error loading font!" << endl;
        exit(EXIT_FAILURE);
    }
}

void menuScreen(RenderWindow &window)
{

    Button b1("New Game", {screenResolution.x / 2 - 60, screenResolution.y / 2 - 120});
    Button b2("Continue", {screenResolution.x / 2 - 57, screenResolution.y / 2 - 60});
    Button b3("Score Board", {screenResolution.x / 2 - 70, screenResolution.y / 2 });
    Button b4("Exit", {screenResolution.x / 2 - 25, screenResolution.y / 2 +60});

    Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                if (b1.isClicked(mousePos))
                {
                    b1.ChangeColor();
                }

                if (b2.isClicked(mousePos))
                {
                    b2.ChangeColor();
                }

                if (b3.isClicked(mousePos))
                {
                    b3.ChangeColor();
                }

                if (b4.isClicked(mousePos))
                {
                    b4.ChangeColor();
                }
            }
        }

        window.clear();

        b1.draw(window);
        b2.draw(window);
        b3.draw(window);
        b4.draw(window);

        window.display();
    }
}

int main()
{

    RenderWindow window(VideoMode(screenResolution.x, screenResolution.y), "Button and Griffin Example");
    window.setFramerateLimit(60);

    // Load the font for Button
    fontLoad();

    // Create a Button
    Button myButton("Click Me", {screenResolution.x / 2 - 50, screenResolution.y / 2 - 5});

    Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                if (myButton.isClicked(mousePos))
                {
                    myButton.ChangeColor();
                    menuScreen(window);
                    exit(EXIT_SUCCESS);
                }
            }
        }

        window.clear();

        myButton.draw(window);

        window.display();
    }

    return 0;
}
*/