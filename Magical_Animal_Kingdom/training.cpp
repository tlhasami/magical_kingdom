#include "training.h"

char Training::arr[12][25];

int Training::training(RenderWindow &window, Player &player, const int selection)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;
    const float cellSize = 50.f; // 50px per cell

    const int cols = screenWidth / cellSize;  // 20 columns
    const int rows = screenHeight / cellSize; // 12 rows

    // Initialize the map
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (i == rows - 1 || j == 0 || j == cols - 1 || j == 8) // walls at left, right, bottom, and vertical wall at column 8
                arr[i][j] = '*';
            else
                arr[i][j] = ' ';
        }
    }

    for (int j = 1; j <= 7; ++j)
        arr[0][j] = '*'; // Top walls at 1-7

    Object wall("b1.png", {0, 0}, {cellSize / 32.f + 0.5f, cellSize / 32.f + 0.7f});
    Object bg("train_1.png", {0, 0}, {screenWidth / 1366.f, screenHeight / 768.f});
    Button back(" <- Back ", {10, 10}, Color(0, 0, 0), Color(128, 0, 128));

    // Setup pet's position in the center of columns 1-7
    Vector2f petStartPosition(130, 170);

    Sprite *selectedPet = nullptr;

    if (selection == 1)
        selectedPet = &player.griffin.sprite;
    else if (selection == 2)
        selectedPet = &player.phoenix.sprite;
    else if (selection == 3)
        selectedPet = &player.dragon.sprite;
    else
        selectedPet = &player.unicorn.sprite;

    selectedPet->setPosition(petStartPosition);

    if (selection == 1)
        selectedPet->setScale(2.f, 2.f); // Increase size
    else if (selection == 2)
        selectedPet->setScale(0.7f, 0.7f); // Increase size
    else if (selection == 3)
        selectedPet->setScale(2.f, 2.f); // Increase size
    else
        selectedPet->setScale(1.6f, 1.6f); // Increase size
    // Falling rectangles
    struct FallingObj
    {
        Object *obj; // dynamically allocated
        bool stopped;
    };

    const int maxFalling = 100;
    FallingObj *fallingRects[maxFalling];
    int totalFalling = 0;

    Clock clock;
    Clock spawnClock;
    const float spawnInterval = 0.8f;

    int collected_points = 0 ;
    Clock surviving ;
    const float survial_interval = 10.f;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        Event event;
        // Handle events
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                // Check if back button clicked
                if (back.isClicked(mousePos))
                {
                    for (int i = 0; i < totalFalling; ++i)
                    {
                        delete fallingRects[i]->obj;
                        delete fallingRects[i];
                    }

                    return -1;
                }

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                {
                    for (int i = 0; i < totalFalling; ++i)
                    {
                        if (!fallingRects[i]->stopped &&
                            fallingRects[i]->obj->sprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                        {
                            delete fallingRects[i]->obj;
                            delete fallingRects[i];

                            for (int j = i; j < totalFalling - 1; ++j)
                                fallingRects[j] = fallingRects[j + 1];

                            --totalFalling;
                            break;
                        }
                    }
                }
            }
        }

        // Update animations
        player.dragon.updateAnimation(deltaTime);
        player.griffin.updateAnimation(deltaTime);
        player.phoenix.updateAnimation(deltaTime);
        player.unicorn.updateAnimation(deltaTime);

        // Spawn falling rectangles
        if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval && totalFalling < maxFalling)
        {
            spawnClock.restart();
            int col = rand() % 10 + 9; // Columns 9 to 18
            Object *newObj = new Object("b1.png", {col * cellSize, 0},{cellSize / 32.f + 0.3f, cellSize / 32.f + 0.7f});

            // Set random color
            newObj->sprite.setColor(Color(rand() % 256, rand() % 256, rand() % 256));

            fallingRects[totalFalling] = new FallingObj{newObj, false};
            ++totalFalling;
        }

        if (surviving.getElapsedTime().asSeconds() >= survial_interval ){
            surviving.restart();
            collected_points += 1;
        }

        float fallSpeed = 350.f; // increased speed

        for (int i = 0; i < totalFalling; ++i)
        {
            if (!fallingRects[i]->stopped)
            {
                fallingRects[i]->obj->sprite.move(0, fallSpeed * deltaTime);
                float y = fallingRects[i]->obj->sprite.getPosition().y;

                // Check bottom or stacking
                if (y + cellSize >= screenHeight - cellSize)
                {
                    fallingRects[i]->obj->sprite.setPosition(
                        fallingRects[i]->obj->sprite.getPosition().x, screenHeight - 2 * cellSize);
                    fallingRects[i]->stopped = true;
                }

                for (int j = 0; j < totalFalling; ++j)
                {
                    if (i != j && fallingRects[j]->stopped)
                    {
                        if (fallingRects[i]->obj->sprite.getGlobalBounds().intersects(fallingRects[j]->obj->sprite.getGlobalBounds()))
                        {
                            float newY = fallingRects[j]->obj->sprite.getPosition().y - cellSize;
                            fallingRects[i]->obj->sprite.setPosition(fallingRects[i]->obj->sprite.getPosition().x, newY);
                            fallingRects[i]->stopped = true;
                            break;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < totalFalling; ++i)
        {
            if (fallingRects[i]->stopped && fallingRects[i]->obj->sprite.getPosition().y <= 5 * cellSize)
            {
                
                for (int i = 0; i < totalFalling; ++i)
                {
                    delete fallingRects[i]->obj;
                    delete fallingRects[i];
                }
                

                return collected_points;
            }
        }

        window.clear();
        bg.draw(window);

        // Draw walls
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (arr[i][j] == '*')
                {
                    wall.changePosition({j * cellSize, i * cellSize});
                    wall.draw(window);
                }
            }
        }

        for (int i = 0; i < totalFalling; ++i)
            fallingRects[i]->obj->draw(window);

        // Draw the pet
        window.draw(*selectedPet);

        // Draw pet details above and attributes below
        Vector2f petPos = selectedPet->getPosition();
        Vector2f petSize(selectedPet->getGlobalBounds().width, selectedPet->getGlobalBounds().height);

        displayText("              Animal Details", {30, 120}, window, 22, Color::White);
        displayText("                  Attributes:", {30, 150}, window, 18, Color::White);
        if (selection == 1)
        {
            displayText("Atk: " + to_string(player.griffin.getAttack()),
                {petPos.x + petSize.x / 2 - 60, petPos.y + petSize.y + 10}, window, 20, Color::Red);
            displayText("Def: " + to_string(player.griffin.getDefence()),
                {petPos.x + petSize.x / 2, petPos.y + petSize.y + 10}, window, 20, Color::Cyan); // Brown
            displayText("HP: " + to_string(player.griffin.getHealth()),
                {petPos.x + petSize.x / 2 + 60, petPos.y + petSize.y + 10}, window, 20, Color::Green);
        }
        else if (selection == 2)
        {
            displayText("Atk: " + to_string(player.phoenix.getAttack()),
                {100, petPos.y + petSize.y + 10}, window, 20, Color::Red);
            displayText("Def: " + to_string(player.phoenix.getDefence()),
                {160, petPos.y + petSize.y + 10}, window, 20, Color::Cyan); // Brown
            displayText("HP: " + to_string(player.phoenix.getHealth()),
                {220, petPos.y + petSize.y + 10}, window, 20, Color::Green);
        }
        else if (selection == 3)
        {
            displayText("Atk: " + to_string(player.dragon.getAttack()),
                {100, petPos.y + petSize.y }, window, 20, Color::Red);
            displayText("Def: " + to_string(player.dragon.getDefence()),
                {160, petPos.y + petSize.y }, window, 20, Color::Cyan); // Brown
            displayText("HP: " + to_string(player.dragon.getHealth()),
                {220, petPos.y + petSize.y }, window, 20, Color::Green);
        }
        else if (selection == 4)
        {
            displayText("Atk: " + to_string(player.unicorn.getAttack()),
                {petPos.x + petSize.x / 2 - 60, petPos.y + petSize.y + 10}, window, 20, Color::Red);
            displayText("Def: " + to_string(player.unicorn.getDefence()),
                {petPos.x + petSize.x / 2 , petPos.y + petSize.y + 10}, window, 20, Color::Cyan); // Brown
            displayText("HP: " + to_string(player.unicorn.getHealth()),
                {petPos.x + petSize.x / 2 + 60, petPos.y + petSize.y + 10}, window, 20, Color::Green);
        }

        displayText("                 Collected Points : " + to_string(collected_points) , {30, screenHeight - 210}, window, 20, Color::Yellow);

        displayText("              Training Session:                   ", {30, screenHeight - 180}, window, 20, Color::White);
        displayText("            Click on red blocks to destroy them before ", {30, screenHeight - 150}, window, 18, Color::White);
        displayText("            they stack up. If the stack reaches 3rd row ", {30, screenHeight - 120}, window, 18, Color::White);
        displayText("            from bottom, you lose.", {30, screenHeight - 90}, window, 18, Color::White);

        back.draw(window);
        window.display();
    }

    for (int i = 0; i < totalFalling; ++i)
    {
        delete fallingRects[i]->obj;
        delete fallingRects[i];
    }

    return -1;
}

/*


void Training::training(RenderWindow &window, Player &player, const int selection)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;
    const float cellSize = 50.f; // 50px per cell

    const int cols = screenWidth / cellSize;  // 20 columns
    const int rows = screenHeight / cellSize; // 12 rows

    // Initialize the map
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (i == rows - 1 || j == 0 || j == cols - 1 || j == 8) // walls at left, right, bottom, and vertical wall at column 8
                arr[i][j] = '*';
            else
                arr[i][j] = ' ';
        }
    }

    for (int j = 1; j <= 7; ++j)
        arr[0][j] = '*'; // Top walls at 1-7

    Object wall("b1.png", {0, 0}, {cellSize / 32.f + 0.5f, cellSize / 32.f + 0.7f});
    Object bg("train_1.png", {0, 0}, {screenWidth / 1366.f, screenHeight / 768.f});
    Button back(" <- Back ", {10, 10}, Color(0, 0, 0), Color(128, 0, 128));

    // Setup pet's position in the center of columns 1-7
    Vector2f petStartPosition(130, 170);

    Sprite *selectedPet = nullptr;

    if (selection == 1)
        selectedPet = &player.griffin.sprite;
    else if (selection == 2)
        selectedPet = &player.phoenix.sprite;
    else if (selection == 3)
        selectedPet = &player.dragon.sprite;
    else
        selectedPet = &player.unicorn.sprite;

    selectedPet->setPosition(petStartPosition);

    if (selection == 1)
        selectedPet->setScale(2.f, 2.f); // Increase size
    else if (selection == 2)
    selectedPet->setScale(0.7f, 0.7f); // Increase size
    else if (selection == 3)
        selectedPet->setScale(2.f, 2.f); // Increase size
    else
        selectedPet->setScale(2.f, 2.f); // Increase size
    // Falling rectangles
    struct FallingRect
    {
        RectangleShape shape;
        bool stopped = false;
    };

    std::vector<FallingRect> fallingRects;

    Clock clock;
    Clock spawnClock;
    const float spawnInterval = 0.8f;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        Event event;
        // Handle events
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                // Check if back button clicked
                if (back.isClicked(mousePos))
                    return;

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                {
                    Vector2i mousePos = Mouse::getPosition(window);

                    if (back.isClicked(mousePos))
                        return;

                    // Check if any falling (non-stopped) rectangle is clicked
                    for (auto it = fallingRects.begin(); it != fallingRects.end();)
                    {
                        if (!it->stopped && it->shape.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)))
                        {
                            it = fallingRects.erase(it); // Remove only if it's still falling
                        }
                        else
                        {
                            ++it;
                        }
                    }
                }
            }
        }

        // Update animations
        player.dragon.updateAnimation(deltaTime);
        player.griffin.updateAnimation(deltaTime);
        player.phoenix.updateAnimation(deltaTime);
        player.unicorn.updateAnimation(deltaTime);

        // Spawn falling rectangles
        if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval)
        {
            spawnClock.restart();

            int spawnColumn = rand() % (18 - 9 + 1) + 9; // Columns 9 to 18

            FallingRect newRect;
            newRect.shape.setSize({cellSize, cellSize});
            newRect.shape.setFillColor(Color::Red);
            newRect.shape.setPosition(spawnColumn * cellSize, 0);
            fallingRects.push_back(newRect);
        }

        // Update falling rectangles
        for (int i = 0; i < fallingRects.size(); ++i)
        {
            if (!fallingRects[i].stopped)
            {
                fallingRects[i].shape.move(0, 200.f * deltaTime);

                // Stop if reached bottom
                if (fallingRects[i].shape.getPosition().y + cellSize >= screenHeight - cellSize)
                {
                    fallingRects[i].shape.setPosition(fallingRects[i].shape.getPosition().x, screenHeight - 2 * cellSize);
                    fallingRects[i].stopped = true;
                }

                // Check for collisions with other stopped rectangles
                for (size_t j = 0; j < fallingRects.size(); ++j)
                {
                    if (i != j && fallingRects[j].stopped)
                    {
                        if (fallingRects[i].shape.getGlobalBounds().intersects(fallingRects[j].shape.getGlobalBounds()))
                        {
                            // Snap the rectangle just above the collided rectangle
                            float newY = fallingRects[j].shape.getPosition().y - cellSize;
                            fallingRects[i].shape.setPosition(fallingRects[i].shape.getPosition().x, newY);
                            fallingRects[i].stopped = true;
                            break;
                        }
                    }
                }
            }
        }

        // After all updates, check if any rectangle has stopped above the critical line (row 8)
        for (auto &rect : fallingRects)
        {
            if (rect.stopped && rect.shape.getPosition().y <= 6 * cellSize)
            {
                displayText("You Lost! Returning...", {screenWidth / 2 - 150, screenHeight / 2}, window, 30, Color::Red);
                window.display();
                sleep(seconds(2));
                return;
            }
        }

        window.clear();
        bg.draw(window);

        // Draw walls
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (arr[i][j] == '*')
                {
                    wall.changePosition({j * cellSize, i * cellSize});
                    wall.draw(window);
                }
            }
        }

        // Draw falling rectangles
        for (auto &rect : fallingRects)
            window.draw(rect.shape);

        // Draw the pet
        window.draw(*selectedPet);

        // Draw pet details above and attributes below
        Vector2f petPos = selectedPet->getPosition();
        Vector2f petSize(selectedPet->getGlobalBounds().width, selectedPet->getGlobalBounds().height);

        if (selection == 1)
        {
            displayText("Griffin", {petPos.x + petSize.x / 2 - 40, petPos.y - 60}, window, 22, Color::White);
            displayText("Body of a lion,\nWings of an eagle.", {petPos.x + petSize.x / 2 - 70, petPos.y - 30}, window, 18, Color::White);
            displayText("Atk: " + to_string(player.griffin.getAttack()) +
                            " Def: " + to_string(player.griffin.getDefence()) +
                            " HP: " + to_string(player.griffin.getHealth()),
                        {petPos.x + petSize.x / 2 - 60, petPos.y + petSize.y + 10}, window, 20, Color::White);
        }
        else if (selection == 2)
        {
            displayText("Phoenix", {petPos.x + petSize.x / 2 - 45, petPos.y - 60}, window, 22, Color::White);
            displayText("Fiery bird,\nRises from ashes.", {petPos.x + petSize.x / 2 - 70, petPos.y - 30}, window, 18, Color::White);
            displayText("Atk: " + to_string(player.phoenix.getAttack()) +
                            " Def: " + to_string(player.phoenix.getDefence()) +
                            " HP: " + to_string(player.phoenix.getHealth()),
                        {petPos.x + petSize.x / 2 - 60, petPos.y + petSize.y + 10}, window, 20, Color::White);
        }
        else if (selection == 3)
        {
            displayText("Dragon", {petPos.x + petSize.x / 2 - 40, petPos.y - 60}, window, 22, Color::White);
            displayText("Powerful beast\nwith fiery breath.", {petPos.x + petSize.x / 2 - 70, petPos.y - 30}, window, 18, Color::White);
            displayText("Atk: " + to_string(player.dragon.getAttack()) +
                            " Def: " + to_string(player.dragon.getDefence()) +
                            " HP: " + to_string(player.dragon.getHealth()),
                        {petPos.x + petSize.x / 2 - 60, petPos.y + petSize.y + 10}, window, 20, Color::White);
        }
        else if (selection == 4)
        {
            displayText("Unicorn", {petPos.x + petSize.x / 2 - 45, petPos.y - 60}, window, 22, Color::White);
            displayText("Mystical horse\nwith magical horn.", {petPos.x + petSize.x / 2 - 70, petPos.y - 30}, window, 18, Color::White);
            displayText("Atk: " + to_string(player.unicorn.getAttack()) +
                            " Def: " + to_string(player.unicorn.getDefence()) +
                            " HP: " + to_string(player.unicorn.getHealth()),
                        {petPos.x + petSize.x / 2 - 60, petPos.y + petSize.y + 10}, window, 20, Color::White);
        }

        displayText("Training Session:", {10, screenHeight - 150}, window, 20, Color::White);
        displayText("Click on red blocks to destroy them before they stack up.", {10, screenHeight - 120}, window, 18, Color::White);
        displayText("If the stack reaches 3rd row from bottom, you lose.", {10, screenHeight - 90}, window, 18, Color::White);

        back.draw(window);
        window.display();
    }
}



*/