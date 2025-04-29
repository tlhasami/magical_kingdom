#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "training.h"

using namespace sf;
using namespace std;

Vector2f screenResolution(1000, 600);

const Color back_C(0, 0, 0);     // Black background for b1
const Color text_C(128, 0, 128); // Purple text for b1

static void fontLoad()
{
    if (!Button::font.loadFromFile("fonts/jersey.ttf"))
    {
        cout << "Error loading font!" << endl;
        exit(EXIT_FAILURE);
    }
}

void savePlayerData(const Player &player, const string &filename)
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    outFile << player.getName() << endl;
    outFile << player.getT1() << " " << player.getT2() << " " << player.getT3() << " "
            << player.getT4() << " " << player.getT5() << " " << player.getT6() << " "
            << player.getGems() << endl;

    outFile << player.griffin.getAttack() << " " << player.griffin.getDefence() << " "
            << player.griffin.getHealth() << " " << player.griffin.getLevel() << endl;
    outFile << "Griffin" << endl;

    outFile << player.phoenix.getAttack() << " " << player.phoenix.getDefence() << " "
            << player.phoenix.getHealth() << " " << player.phoenix.getLevel() << endl;
    outFile << "Phoenix" << endl;

    outFile << player.dragon.getAttack() << " " << player.dragon.getDefence() << " "
            << player.dragon.getHealth() << " " << player.dragon.getLevel() << endl;
    outFile << "Dragon" << endl;

    outFile << player.unicorn.getAttack() << " " << player.unicorn.getDefence() << " "
            << player.unicorn.getHealth() << " " << player.unicorn.getLevel() << endl;
    outFile << "Unicorn" << endl;

    outFile.close();
}

void loadPlayerData(Player &player, const string &filename)
{
    ifstream inFile(filename);
    if (!inFile)
    {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string name;
    inFile >> ws;
    getline(inFile, name);
    player.setName(name);

    int t1, t2, t3, t4, t5, t6, gems;
    inFile >> t1 >> t2 >> t3 >> t4 >> t5 >> t6 >> gems;
    player.setT1(t1);
    player.setT2(t2);
    player.setT3(t3);
    player.setT4(t4);
    player.setT5(t5);
    player.setT6(t6);
    player.setGems(gems);

    int attack, defence, health, level;
    string petName;

    inFile >> attack >> defence >> health >> level >> ws;
    getline(inFile, petName);
    if (petName == "Griffin")
    {
        player.griffin.setAttack(attack);
        player.griffin.setDefence(defence);
        player.griffin.setHealth(health);
        player.griffin.setLevel(level);
    }

    inFile >> attack >> defence >> health >> level >> ws;
    getline(inFile, petName);
    if (petName == "Phoenix")
    {
        player.phoenix.setAttack(attack);
        player.phoenix.setDefence(defence);
        player.phoenix.setHealth(health);
        player.phoenix.setLevel(level);
    }

    inFile >> attack >> defence >> health >> level >> ws;
    getline(inFile, petName);
    if (petName == "Dragon")
    {
        player.dragon.setAttack(attack);
        player.dragon.setDefence(defence);
        player.dragon.setHealth(health);
        player.dragon.setLevel(level);
    }

    inFile >> attack >> defence >> health >> level >> ws;
    getline(inFile, petName);
    if (petName == "Unicorn")
    {
        player.unicorn.setAttack(attack);
        player.unicorn.setDefence(defence);
        player.unicorn.setHealth(health);
        player.unicorn.setLevel(level);
    }

    inFile.close();
}

void add_counts(RenderWindow &window, Player &player, int selectedPet = -1, int point_collected = 0)
{

    Object bg("train_1.png", {0, 0}, {screenResolution.x / 1366.f, screenResolution.y / 768.f});

    Button addHealthButton("  Add  Health ", {screenResolution.x / 2 + 150, screenResolution.y / 2 - 110}, Color::Green, Color::White);
    Button addAttackButton("  Add  Attack ", {screenResolution.x / 2 + 150, screenResolution.y / 2 - 40}, Color::Red, Color::White);
    Button addDefenceButton("  Add Defence ", {screenResolution.x / 2 + 150, screenResolution.y / 2 + 30}, Color::Cyan, Color::White);

    Vector2f petStartPosition(130, 170);

    if (selectedPet == 1)
    {
        player.griffin.changePosition({petStartPosition});
        player.griffin.changeScale({2.5f, 2.5f});
    }
    else if (selectedPet == 2)
    {
        player.phoenix.changePosition({petStartPosition});
        player.phoenix.changeScale({.8f, .8f});
    }
    else if (selectedPet == 3)
    {
        player.dragon.changePosition({petStartPosition});
        player.dragon.changeScale({2.f, 2.f});
    }
    else if (selectedPet == 4)
    {
        player.unicorn.changePosition({petStartPosition});
        player.unicorn.changeScale({2.5f, 2.5f});
    }

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

                if (addHealthButton.isClicked(mousePos) && point_collected > 0)
                {
                    switch (selectedPet)
                    {
                    case 1:
                        player.griffin.addHealth(5);
                        player.griffin.increaseLevel(1);
                        point_collected--;
                        break;
                    case 2:
                        player.phoenix.addHealth(5);
                        player.phoenix.increaseLevel(1);
                        point_collected--;
                        break;
                    case 3:
                        player.dragon.addHealth(5);
                        player.dragon.increaseLevel(1);
                        point_collected--;
                        break;
                    case 4:
                        player.unicorn.addHealth(5);
                        player.unicorn.increaseLevel(1);
                        point_collected--;
                        break;
                    }
                }

                if (addAttackButton.isClicked(mousePos) && point_collected > 0)
                {
                    switch (selectedPet)
                    {
                    case 1:
                        player.griffin.addAttack(5);
                        player.griffin.increaseLevel(1);
                        point_collected--;
                        break;
                    case 2:
                        player.phoenix.addAttack(5);
                        player.phoenix.increaseLevel(1);
                        point_collected--;
                        break;
                    case 3:
                        player.dragon.addAttack(5);
                        player.dragon.increaseLevel(1);
                        point_collected--;
                        break;
                    case 4:
                        player.unicorn.addAttack(5);
                        player.unicorn.increaseLevel(1);
                        point_collected--;
                        break;
                    }
                }

                if (addDefenceButton.isClicked(mousePos) && point_collected > 0)
                {
                    switch (selectedPet)
                    {
                    case 1:
                        player.griffin.addDefence(5);
                        player.griffin.increaseLevel(1);
                        point_collected--;
                        break;
                    case 2:
                        player.phoenix.addDefence(5);
                        player.phoenix.increaseLevel(1);
                        point_collected--;
                        break;
                    case 3:
                        player.dragon.addDefence(5);
                        player.dragon.increaseLevel(1);
                        point_collected--;
                        break;
                    case 4:
                        player.unicorn.addDefence(5);
                        player.unicorn.increaseLevel(1);
                        point_collected--;
                        break;
                    }
                }
            }
        }

        // Update the animations of All pets every time
        player.dragon.updateAnimation(deltaTime);
        player.griffin.updateAnimation(deltaTime);
        player.phoenix.updateAnimation(deltaTime);
        player.unicorn.updateAnimation(deltaTime);

        window.clear();

        bg.draw(window);

        switch (selectedPet)
        {
        case 1:
            player.griffin.draw(window, false);
            displayText("    -> Level: " + to_string(player.griffin.getLevel()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 - 130}, window, 30, Color::Yellow);
            displayText("      Health: " + to_string(player.griffin.getHealth()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 - 80}, window, 30, Color::Green);
            displayText("      Attack: " + to_string(player.griffin.getAttack()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 - 30}, window, 30, Color::Red);
            displayText("      Defense: " + to_string(player.griffin.getDefence()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 + 20}, window, 30, Color::Cyan);
            break;
        case 2:
            player.phoenix.draw(window, false);
            displayText("    -> Level: " + to_string(player.phoenix.getLevel()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 - 130}, window, 30, Color::Yellow);
            displayText("      Health: " + to_string(player.phoenix.getHealth()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 - 80}, window, 30, Color::Green);
            displayText("      Attack: " + to_string(player.phoenix.getAttack()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 - 30}, window, 30, Color::Red);
            displayText("      Defense: " + to_string(player.phoenix.getDefence()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 + 20}, window, 30, Color::Cyan);
            break;
        case 3:
            player.dragon.draw(window, false);
            displayText("    -> Level: " + to_string(player.dragon.getLevel()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 - 130}, window, 30, Color::Yellow);
            displayText("      Health: " + to_string(player.dragon.getHealth()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 - 80}, window, 30, Color::Green);
            displayText("      Attack: " + to_string(player.dragon.getAttack()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 - 30}, window, 30, Color::Red);
            displayText("      Defense: " + to_string(player.dragon.getDefence()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 + 20}, window, 30, Color::Cyan);
            break;
        case 4:
            player.unicorn.draw(window, false);
            displayText("    -> Level: " + to_string(player.unicorn.getLevel()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 - 130}, window, 30, Color::Yellow);
            displayText("      Health: " + to_string(player.unicorn.getHealth()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 - 80}, window, 30, Color::Green);
            displayText("      Attack: " + to_string(player.unicorn.getAttack()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 - 30}, window, 30, Color::Red);
            displayText("      Defense: " + to_string(player.unicorn.getDefence()),
                        {screenResolution.x / 2 - 100, screenResolution.y / 2 + 20}, window, 30, Color::Cyan);
            break;
        }

        // Draw buttons
        addHealthButton.draw(window);
        addAttackButton.draw(window);
        addDefenceButton.draw(window);

        // Display points collected
        displayText("Points Collected: " + to_string(point_collected),
                    {screenResolution.x / 2 - 100, screenResolution.y / 2 - 110}, window, 30, Color::White);

        window.display();

        if (point_collected == 0)
            return;
    }
}

int selectPet(RenderWindow &window, Player &player)
{
    Object bg("train_1.png", {0, 0}, {screenResolution.x / 1366.f, screenResolution.y / 768.f});

    player.setPostionTraining();

    Clock clock;
    // Buttons for each pet
    Button griffinButton("Select Griffin", {100, 220}, Color(255, 215, 0), Color::Black);
    Button phoenixButton("Select Phoenix", {600, 220}, Color(220, 20, 60), Color::White);
    Button dragonButton("Select Dragon", {100, 500}, Color(70, 130, 180), Color::White);
    Button unicornButton("Select Unicorn", {600, 500}, Color(218, 112, 214), Color::Black);

    Button back(" <- Back ", {10, 10}, back_C, text_C);

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

                if (griffinButton.isClicked(mousePos))
                {
                    return 1;
                }

                if (phoenixButton.isClicked(mousePos))
                {
                    return 2;
                }

                if (dragonButton.isClicked(mousePos))
                {
                    return 3;
                }

                if (unicornButton.isClicked(mousePos))
                {
                    return 4;
                }

                if (back.isClicked(mousePos))
                {
                    return 0;
                }
            }
        }

        // Update the animations of All pets every time
        player.dragon.updateAnimation(deltaTime);
        player.griffin.updateAnimation(deltaTime);
        player.phoenix.updateAnimation(deltaTime);
        player.unicorn.updateAnimation(deltaTime);

        window.clear();

        bg.draw(window);

        // Draw All Pets
        player.griffin.draw(window, false);
        player.dragon.draw(window, false);
        player.phoenix.draw(window, false);
        player.unicorn.draw(window, false);

        // Draw buttons
        griffinButton.draw(window);
        phoenixButton.draw(window);
        dragonButton.draw(window);
        unicornButton.draw(window);

        back.draw(window);

        // // Display pet information and stats
        // Display pet information and stats

        // Griffin (top-left)
        displayText("Griffin: A majestic creature with sharp talons.",
                    {screenResolution.x / 2 - 315, screenResolution.y / 2 - 200}, window, 20, Color::White);
        displayText("Attack: " + to_string(player.griffin.getAttack()) +
                        " | Defense: " + to_string(player.griffin.getDefence()) +
                        " | Health: " + to_string(player.griffin.getHealth()),
                    {screenResolution.x / 2 - 300, screenResolution.y / 2 - 180}, window, 20, Color::White);

        // Phoenix (top-right)
        displayText("Phoenix: A fiery bird that rises from Ice.",
                    {screenResolution.x / 2 + 170, screenResolution.y / 2 - 200}, window, 20, Color::White);
        displayText("Attack: " + to_string(player.phoenix.getAttack()) +
                        " | Defense: " + to_string(player.phoenix.getDefence()) +
                        " | Health: " + to_string(player.phoenix.getHealth()),
                    {screenResolution.x / 2 + 200, screenResolution.y / 2 - 180}, window, 20, Color::White);

        // Dragon (bottom-left)
        displayText("Dragon: A powerful beast with fiery breath.",
                    {screenResolution.x / 2 - 280, screenResolution.y / 2 + 90}, window, 20, Color::White);
        displayText("Attack: " + to_string(player.dragon.getAttack()) +
                        " | Defense: " + to_string(player.dragon.getDefence()) +
                        " | Health: " + to_string(player.dragon.getHealth()),
                    {screenResolution.x / 2 - 260, screenResolution.y / 2 + 110}, window, 20, Color::White);

        // Unicorn (bottom-right)
        displayText("Unicorn: A mystical horse with a magical horn.",
                    {screenResolution.x / 2 + 150, screenResolution.y / 2 + 90}, window, 20, Color::White);
        displayText("Attack: " + to_string(player.unicorn.getAttack()) +
                        " | Defense: " + to_string(player.unicorn.getDefence()) +
                        " | Health: " + to_string(player.unicorn.getHealth()),
                    {screenResolution.x / 2 + 180, screenResolution.y / 2 + 110}, window, 20, Color::White);

        window.display();
    }

    return -1;
}

void training(RenderWindow &window, Player &player)
{

    int selectedPet = -1;
    int point_collected = 0;

    while (selectedPet != 0)
    {

        selectedPet = selectPet(window, player);

        if (selectedPet >= 1 && selectedPet <= 4)
        {

            point_collected = Training::training(window, player, selectedPet);

            if (point_collected != -1)
                add_counts(window, player, selectedPet, point_collected);
        }
    }

    player.setPostionsDefault();
}

void Shop(RenderWindow &window, Player &player)
{

    Object bg("bg1.png", {0, 0}, {screenResolution.x / 1366.f, screenResolution.y / 768.f});
    // Back Button
    Button back(" <- Back ", {100, screenResolution.y / 2 + 200}, back_C, text_C);

    // Buy Buttons with custom colors
    Button buy_1("Buy for 5", {100, 200}, back_C, text_C); // Dark background, light text
    Button buy_2("Buy for 5", {300, 200}, back_C, text_C); // Dark background, light text
    Button buy_3("Buy for 5", {500, 200}, back_C, text_C); // Blue background, light text
    Button buy_4("Buy for 7", {100, 400}, back_C, text_C); // Yellow background, dark text
    Button buy_5("Buy for 8", {300, 400}, back_C, text_C); // Pink background, dark text
    Button buy_6("Buy for 2", {500, 400}, back_C, text_C); // Green background, light text

    // Objects
    Object t_1("blue_portion.png", {100, 100}, {3.f, 3.f});
    Object t_2("green_portion.png", {300, 100}, {3.f, 3.f});
    Object t_3("red_portion.png", {500, 100}, {3.f, 3.f});
    Object t_4("feather.png", {100, 300}, {3.f, 3.f});
    Object t_5("mashroom.png", {300, 300}, {3.f, 3.f});
    Object t_6("raddis.png", {500, 300}, {3.f, 3.f});
    Object gems("gems.png", {700, 200}, {3.f, 3.f});

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                if (back.isClicked(mousePos)) // Back
                {
                    back.ChangeColor();
                    return;
                }

                if (buy_1.isClicked(mousePos) && player.getGems() >= 5)
                {
                    player.addT1(1);
                    player.addGems(-5);
                }

                if (buy_2.isClicked(mousePos) && player.getGems() >= 5)
                {
                    player.addT2(1);
                    player.addGems(-5);
                }

                if (buy_3.isClicked(mousePos) && player.getGems() >= 5)
                {
                    player.addT3(1);
                    player.addGems(-5);
                }

                if (buy_4.isClicked(mousePos) && player.getGems() >= 7)
                {
                    player.addT4(1);
                    player.addGems(-7);
                }

                if (buy_5.isClicked(mousePos) && player.getGems() >= 8)
                {
                    player.addT5(1);
                    player.addGems(-8);
                }

                if (buy_6.isClicked(mousePos) && player.getGems() >= 2)
                {
                    player.addT6(1);
                    player.addGems(-2);
                }
            }
        }

        window.clear();

        bg.draw(window);
        // Draw all Buttons
        back.draw(window);

        // Draw All Items
        t_1.draw(window);
        t_2.draw(window);
        t_3.draw(window);
        t_4.draw(window);
        t_5.draw(window);
        t_6.draw(window);
        gems.draw(window);

        displayText("x" + to_string(player.getT1()), {150 + 15, 170}, window, 25, Color::White);
        displayText("x" + to_string(player.getT2()), {350 + 15, 170}, window, 25, Color::White);
        displayText("x" + to_string(player.getT3()), {550 + 15, 170}, window, 25, Color::White);
        displayText("x" + to_string(player.getT4()), {150 + 15, 370}, window, 25, Color::White);
        displayText("x" + to_string(player.getT5()), {350 + 15, 370}, window, 25, Color::White);
        displayText("x" + to_string(player.getT6()), {550 + 15, 370}, window, 25, Color::White);

        displayText("BLUE PORTION", {100, 75}, window, 25, Color::White);
        displayText("GREEN PORTION", {300, 75}, window, 25, Color::White);
        displayText("RED PORTION", {500, 75}, window, 25, Color::White);
        displayText("FEATHER", {100, 275}, window, 25, Color::White);
        displayText("MASHROOM", {300, 275}, window, 25, Color::White);
        displayText("RADDIS", {500, 275}, window, 25, Color::White);
        displayText("GEMS", {700, 175}, window, 25, Color::White);

        displayText("x" + to_string(player.getGems()), {700, 300}, window, 35, Color::White);

        buy_1.draw(window);
        buy_2.draw(window);
        buy_3.draw(window);
        buy_4.draw(window);
        buy_5.draw(window);
        buy_6.draw(window);

        window.display();
    }
}

void InventoryCheck(RenderWindow &window, Player &player)
{

    Object bg("bg1.png", {0, 0}, {screenResolution.x / 1366.f, screenResolution.y / 768.f});

    Button back(" <- Back ", {100, screenResolution.y / 2 + 200}, back_C, text_C);

    Object t_1("blue_portion.png", {100, 100}, {3.f, 3.f});
    Object t_2("green_portion.png", {300, 100}, {3.f, 3.f});
    Object t_3("red_portion.png", {500, 100}, {3.f, 3.f});
    Object t_4("feather.png", {100, 300}, {3.f, 3.f});
    Object t_5("mashroom.png", {300, 300}, {3.f, 3.f});
    Object t_6("raddis.png", {500, 300}, {3.f, 3.f});
    Object gems("gems.png", {700, 200}, {3.f, 3.f});

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                if (back.isClicked(mousePos)) // Back
                {
                    back.ChangeColor();
                    return;
                }
            }
        }

        window.clear();

        bg.draw(window);
        // Draw all Buttons
        back.draw(window);

        // Draw All Items

        t_1.draw(window);
        t_2.draw(window);
        t_3.draw(window);
        t_4.draw(window);
        t_5.draw(window);
        t_6.draw(window);
        gems.draw(window);

        displayText("BLUE PORTION", {100, 75}, window, 25, Color::White);
        displayText("GREEN PORTION", {300, 75}, window, 25, Color::White);
        displayText("RED PORTION", {500, 75}, window, 25, Color::White);
        displayText("FEATHER", {100, 275}, window, 25, Color::White);
        displayText("MASHROOM", {300, 275}, window, 25, Color::White);
        displayText("RADDIS", {500, 275}, window, 25, Color::White);
        displayText("GEMS", {700, 175}, window, 25, Color::White);

        displayText("x" + to_string(player.getT1()), {100, 200}, window, 35, Color::White);
        displayText("x" + to_string(player.getT2()), {300, 200}, window, 35, Color::White);
        displayText("x" + to_string(player.getT3()), {500, 200}, window, 35, Color::White);
        displayText("x" + to_string(player.getT4()), {100, 400}, window, 35, Color::White);
        displayText("x" + to_string(player.getT5()), {300, 400}, window, 35, Color::White);
        displayText("x" + to_string(player.getT6()), {500, 400}, window, 35, Color::White);
        displayText("x" + to_string(player.getGems()), {700, 300}, window, 35, Color::White);

        window.display();
    }
}

string askName(RenderWindow &window)
{

    Object bg("name.png", {0, 0}, {screenResolution.x / 1366.f, screenResolution.y / 768.f});
    string playerName = "";
    Text inputText;
    inputText.setFont(Button::font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(Color::White);
    inputText.setPosition(screenResolution.x / 2 - 160, screenResolution.y / 2 - 10);

    Text promptText;
    promptText.setFont(Button::font);
    promptText.setCharacterSize(40);
    promptText.setFillColor(Color::White);
    promptText.setString("Enter your Username:");
    promptText.setPosition(screenResolution.x / 2 - 165, screenResolution.y / 2 - 70);

    RectangleShape inputBackground;
    inputBackground.setSize(Vector2f(400, 50));
    inputBackground.setFillColor(Color::Black);
    inputBackground.setPosition(screenResolution.x / 2 - 200, screenResolution.y / 2 - 10);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode == '\b' && !playerName.empty()) // Handle backspace
                {
                    playerName.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\b') // Handle valid characters
                {
                    playerName += static_cast<char>(event.text.unicode);
                }
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && !playerName.empty())
            {
                return playerName;
            }
        }

        inputText.setString(playerName + "_");

        window.clear();
        bg.draw(window);
        window.draw(inputBackground);
        window.draw(promptText);
        window.draw(inputText);
        window.display();
    }

    return playerName;
}

void Game_Menu(RenderWindow &window)
{

    Object bg("bg1.png", {0, 0}, {screenResolution.x / 1366.f, screenResolution.y / 768.f});

    // Button definitions with assigned colors
    Button b1("Battle", {70 + 100, screenResolution.y / 2 - 120 - 60}, back_C, text_C);
    Button b2("Guild Section", {20 + 100 + 10, screenResolution.y / 2 - 60 - 60}, back_C, text_C);
    Button b3("Training", {50 + 100 + 5, screenResolution.y / 2 - 60}, back_C, text_C);
    Button b4("Inventory", {40 + 100, screenResolution.y / 2}, back_C, text_C);
    Button b5("Shop", {70 + 100, screenResolution.y / 2 + 60}, back_C, text_C);
    Button b6("Exit", {75 + 100, screenResolution.y / 2 + 120}, back_C, text_C);

    Clock clock;

    string name = askName(window);
    

    Player player(name);
    savePlayerData(player, "DataBase/" + name + ".txt");

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

                if (b1.isClicked(mousePos)) // Battle
                {
                }

                if (b2.isClicked(mousePos)) // Guild Working
                {
                }

                if (b3.isClicked(mousePos)) // Training  Section
                {
                    training(window, player);
                    player.setPostionsDefault();
                }

                if (b4.isClicked(mousePos)) // Inventory
                {
                    InventoryCheck(window, player);
                    player.setPostionsDefault();
                }

                if (b5.isClicked(mousePos)) // Shop
                {
                    Shop(window, player);
                    player.setPostionsDefault();
                }

                if (b6.isClicked(mousePos)) // Leaving the Game
                {
                    b6.ChangeColor();
                    player.setPostionsDefault();
                    return;
                }
            }
        }

        // Update the animations of All pets every time
        player.dragon.updateAnimation(deltaTime);
        player.griffin.updateAnimation(deltaTime);
        player.phoenix.updateAnimation(deltaTime);
        player.unicorn.updateAnimation(deltaTime);

        window.clear();

        bg.draw(window);

        // Display a welcome message at the top center of the screen
        displayText("Hello " + name + " ! ", {screenResolution.x / 2 - 100, 20}, window, 40, Color(255, 215, 0));

        // Draw all Buttons
        b1.draw(window);
        b2.draw(window);
        b3.draw(window);
        b4.draw(window);
        b5.draw(window);
        b6.draw(window);

        // Draw All Pets
        player.griffin.draw(window, false);
        player.dragon.draw(window, false);
        player.phoenix.draw(window, false);
        player.unicorn.draw(window, false);

        // Display Names
        displayText("Griffin ( Level " + to_string(player.griffin.getLevel()) + " ) ", {470, 250}, window, 30, Color::White);
        displayText("Dragon ( Level " + to_string(player.dragon.getLevel()) + " ) ", {470, 530}, window, 30, Color::White);
        displayText("Phoenix ( Level " + to_string(player.phoenix.getLevel()) + " ) ", {700, 250}, window, 30, Color::White);
        displayText("Unicorn ( Level " + to_string(player.unicorn.getLevel()) + " ) ", {700, 530}, window, 30, Color::White);

        window.display();
    }
}

// void Game_Menu(RenderWindow &window, Player &player)
// {

//     Object bg("bg1.png", {0, 0}, {screenResolution.x / 1366.f, screenResolution.y / 768.f});

//     // Button definitions with assigned colors
//     Button b1("Battle", {70 + 100, screenResolution.y / 2 - 120 - 60}, back_C, text_C);
//     Button b2("Guild Section", {20 + 100 + 10, screenResolution.y / 2 - 60 - 60}, back_C, text_C);
//     Button b3("Training", {50 + 100 + 5, screenResolution.y / 2 - 60}, back_C, text_C);
//     Button b4("Inventory", {40 + 100, screenResolution.y / 2}, back_C, text_C);
//     Button b5("Shop", {70 + 100, screenResolution.y / 2 + 60}, back_C, text_C);
//     Button b6("Exit", {75 + 100, screenResolution.y / 2 + 120}, back_C, text_C);

//     Clock clock;

//     while (window.isOpen())
//     {
//         float deltaTime = clock.restart().asSeconds();

//         Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == Event::Closed)
//                 window.close();

//             if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
//             {
//                 Vector2i mousePos = Mouse::getPosition(window);

//                 if (b1.isClicked(mousePos)) // Battle
//                 {
//                 }

//                 if (b2.isClicked(mousePos)) // Guild Working
//                 {
//                 }

//                 if (b3.isClicked(mousePos)) // Training  Section
//                 {
//                     training(window, player);
//                 }

//                 if (b4.isClicked(mousePos)) // Inventory
//                 {
//                     InventoryCheck(window, player);
//                     player.setPostionsDefault();
//                 }

//                 if (b5.isClicked(mousePos)) // Shop
//                 {
//                     Shop(window, player);
//                     player.setPostionsDefault();
//                 }

//                 if (b6.isClicked(mousePos)) // Leaving the Game
//                 {
//                     b6.ChangeColor();
//                     savePlayerData(player, "progress.txt");
//                     return;
//                 }
//             }
//         }

//         // Update the animations of All pets every time
//         player.dragon.updateAnimation(deltaTime);
//         player.griffin.updateAnimation(deltaTime);
//         player.phoenix.updateAnimation(deltaTime);
//         player.unicorn.updateAnimation(deltaTime);

//         window.clear();

//         bg.draw(window);

//         // Display a welcome message at the top center of the screen
//         displayText("Hello " + player.getName() + " ! ", {screenResolution.x / 2 - 100, 20}, window, 40, Color(255, 215, 0));

//         // Draw all Buttons
//         b1.draw(window);
//         b2.draw(window);
//         b3.draw(window);
//         b4.draw(window);
//         b5.draw(window);
//         b6.draw(window);

//         // Draw All Pets
//         player.griffin.draw(window, false);
//         player.dragon.draw(window, false);
//         player.phoenix.draw(window, false);
//         player.unicorn.draw(window, false);

//         // Display Names
//         displayText("Griffin ( Level " + to_string(player.griffin.getLevel()) + " ) ", {470, 250}, window, 30, Color::White);
//         displayText("Dragon ( Level " + to_string(player.dragon.getLevel()) + " ) ", {470, 530}, window, 30, Color::White);
//         displayText("Phoenix ( Level " + to_string(player.phoenix.getLevel()) + " ) ", {700, 250}, window, 30, Color::White);
//         displayText("Unicorn ( Level " + to_string(player.unicorn.getLevel()) + " ) ", {700, 530}, window, 30, Color::White);

//         window.display();
//     }
// }

void ContinuedGame(RenderWindow &window)
{

    Player player("unknown");

    string name = askName(window);

    loadPlayerData(player, "DataBase" + name + ".txt");
    // Print all the attribute info of the player
    cout << "Player Name: " << player.getName() << endl;
    cout << "T1: " << player.getT1() << ", T2: " << player.getT2() << ", T3: " << player.getT3()
         << ", T4: " << player.getT4() << ", T5: " << player.getT5() << ", T6: " << player.getT6() << endl;
    cout << "Gems: " << player.getGems() << endl;

    cout << "Griffin - Attack: " << player.griffin.getAttack() << ", Defense: " << player.griffin.getDefence()
         << ", Health: " << player.griffin.getHealth() << ", Level: " << player.griffin.getLevel() << endl;

    cout << "Phoenix - Attack: " << player.phoenix.getAttack() << ", Defense: " << player.phoenix.getDefence()
         << ", Health: " << player.phoenix.getHealth() << ", Level: " << player.phoenix.getLevel() << endl;

    cout << "Dragon - Attack: " << player.dragon.getAttack() << ", Defense: " << player.dragon.getDefence()
         << ", Health: " << player.dragon.getHealth() << ", Level: " << player.dragon.getLevel() << endl;

    cout << "Unicorn - Attack: " << player.unicorn.getAttack() << ", Defense: " << player.unicorn.getDefence()
         << ", Health: " << player.unicorn.getHealth() << ", Level: " << player.unicorn.getLevel() << endl;

    Game_Menu(window);
}

void ScoreBoard(RenderWindow &window)
{

    Object bg("bg1.png", {0, 0}, {screenResolution.x / 1366.f, screenResolution.y / 768.f});

    Button back(" <- Back ", {100, screenResolution.y / 2 + 200}, back_C, text_C);

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                if (back.isClicked(mousePos))
                {
                    return;
                }
            }
        }

        window.clear();

        bg.draw(window);

        // Display a note in the center of the screen
        displayText("No current Guild has been formed.",
                    {screenResolution.x / 2 - 200, screenResolution.y / 2 - 20},
                    window, 30, Color::White);

        back.draw(window);
        window.display();
    }
}

bool ConfirmationNewGame(RenderWindow &window)
{
    Object bg("bg1.png", {0, 0}, {screenResolution.x / 1366.f, screenResolution.y / 768.f});

    Button yesButton("Yes", {screenResolution.x / 2 - 100, screenResolution.y / 2}, back_C, text_C);
    Button noButton("No", {screenResolution.x / 2 + 50, screenResolution.y / 2}, back_C, text_C);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                if (yesButton.isClicked(mousePos))
                {
                    return true;
                }

                if (noButton.isClicked(mousePos))
                {
                    return false;
                }
            }
        }

        window.clear();

        bg.draw(window);
        displayText("Confirm: You will lose all previous progress!", {screenResolution.x / 2 - 250, screenResolution.y / 2 - 50}, window, 30, Color::White);
        yesButton.draw(window);
        noButton.draw(window);

        window.display();
    }

    return false;
}

void menuScreen(RenderWindow &window)
{
    Object bg("bg1.png", {0, 0}, {screenResolution.x / 1366.f, screenResolution.y / 768.f});

    Color back_black(0, 0, 0);      // Black background
    Color text_purple(128, 0, 128); // Light purple text

    Button b1("New Game", {screenResolution.x / 2 - 60, screenResolution.y / 2 - 120}, back_black, text_purple);
    Button b2("Continue", {screenResolution.x / 2 - 55, screenResolution.y / 2 - 60}, back_black, text_purple);
    Button b3("Score Board", {screenResolution.x / 2 - 70, screenResolution.y / 2}, back_black, text_purple);
    Button b4("Exit", {screenResolution.x / 2 - 25, screenResolution.y / 2 + 60}, back_black, text_purple);

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

                if (b1.isClicked(mousePos)) // New Game
                {

                    if (ConfirmationNewGame(window))
                    {
                        Game_Menu(window);
                    }
                }

                if (b2.isClicked(mousePos)) // Continue
                {
                    ContinuedGame(window);
                }

                if (b3.isClicked(mousePos)) // Score Board
                {
                    ScoreBoard(window);
                }

                if (b4.isClicked(mousePos)) // Leaving the Game
                {
                    b4.ChangeColor();
                    exit(EXIT_SUCCESS);
                }
            }
        }

        window.clear();

        bg.draw(window);

        b1.draw(window);
        b2.draw(window);
        b3.draw(window);
        b4.draw(window);

        window.display();
    }
}

int main()
{

    RenderWindow window(VideoMode(screenResolution.x, screenResolution.y), "MAGICAL ANIMAL KINGDOM");
    window.setFramerateLimit(60);

    // Load the font for Button
    fontLoad();

    Object bg("bg3.png", {0, 0}, {screenResolution.x / 1366.f, screenResolution.y / 768.f});
    // Create a Button
    Button myButton("HELLO WORLD", {screenResolution.x / 2 - 50, screenResolution.y / 2 - 60});

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
        bg.draw(window);
        displayText("CLICK ME!", {screenResolution.x / 2 - 50, screenResolution.y / 2 - 50}, window, 30, Color::White);

        window.display();
    }

    return 0;
}