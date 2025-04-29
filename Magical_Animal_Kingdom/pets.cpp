#include "pets.h"

// Constructor for Pet
Pet::Pet(std::string path, float startX, float startY, float scaleX, float scaleY, int totalFrames, const std::string &name)
    : Object(path, {startX, startY}, {scaleX, scaleY}),
      TotalFrames(totalFrames), currentFrame(0), animationTimer(0.0f), petName(name),
      healthBar(Vector2f(startX, startY - 20.f), Vector2f(120.f, 10.f)), level(1)
{
}

void Pet::takeDamage(int amount)
{
    int damageAfterDefence = amount - Defence;
    if (damageAfterDefence < 0)
        damageAfterDefence = 0;

    Health -= damageAfterDefence;
    if (Health < 0)
        Health = 0;
}

void Pet::addHealth(int val){
    Health += val;
}
void Pet::addDefence(int val){
    Defence += val;
}
void Pet::addAttack(int val){
    Attack += val;
}

void Pet::increaseAttack(int amount)
{
    Attack += amount;
}

void Pet::increaseDefence(int amount)
{
    Defence += amount;
}

void Pet::increaseHealth(int amount)
{
    Health += amount;
    if (Health > MaxHealth)
        Health = MaxHealth;
}

bool Pet::isAlive() const
{
    return Health > 0;
}

void Unicorn::updateAnimation(float deltaTime)
{
    animationTimer += deltaTime;

    if (animationTimer >= 0.2f)
    {
        currentFrame = (currentFrame + 1) % TotalFrames;
        setIntRect(currentFrame * (500 / 8) + 5, 0, 500 / 8 + 6.5f, 121);
        animationTimer = 0.0f;
    }

    healthBar.setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y - 20.f));
    healthBar.update(Health, MaxHealth);
}

int Pet::getLevel() const
{
    return level;
}

void Pet::increaseLevel(int up = 1)
{
    level += up;
}

void Phoenix::updateAnimation(float deltaTime)
{
    animationTimer += deltaTime;

    if (animationTimer >= 0.15f)
    {
        currentFrame = (currentFrame + 1) % TotalFrames;

        switch (currentFrame)
        {
        case 0:
            setIntRect(30, 20, 400, 200);
            break;
        case 1:
            setIntRect(30, 250, 400, 200);
            break;
        case 2:
            setIntRect(30, 500, 400, 200);
            break;
        case 3:
            setIntRect(30, 750, 400, 200);
            break;
        case 4:
            setIntRect(30, 750, 350, 200);
            break;
        }

        animationTimer = 0.0f;
    }

    healthBar.setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y - 20.f));
    healthBar.update(Health, MaxHealth);
}

void Griffin::updateAnimation(float deltaTime)
{
    animationTimer += deltaTime;

    if (animationTimer >= 0.2f)
    {
        currentFrame = (currentFrame + 1) % TotalFrames;
        switch (currentFrame)
        {
        case 0:
            setIntRect(2, 0, 72, 90);
            break;
        case 1:
            setIntRect(71, 0, 72, 90);
            break;
        case 2:
            setIntRect(138, 0, 72, 90);
            break;
        case 3:
            setIntRect(225 - 22, 0, 72, 90);
            break;
        case 4:
            setIntRect(300 - 30, 0, 72, 90);
            break;
        case 5:
            setIntRect(375 - 30, 0, 72, 90);
            break;
        case 6:
            setIntRect(450 - 30, 0, 72, 90);
            break;
        case 7:
            setIntRect(525 - 33, 0, 72, 90);
            break;
        case 8:
            setIntRect(600 - 36, 0, 72, 90);
            break;
        }
        animationTimer = 0.05f; // Reset the timer for the next frame
    }

    healthBar.setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y - 20.f));
    healthBar.update(Health, MaxHealth);
}

void Dragon::updateAnimation(float deltaTime)
{
    animationTimer += deltaTime;

    if (animationTimer >= 0.2f)
    {
        currentFrame = (currentFrame + 1) % TotalFrames;

        if (currentFrame < 4)
        {
            setIntRect(currentFrame * 119, 0, 119, 100);
        }
        else
        {
            switch (currentFrame)
            {
            case 4:
                setIntRect(0, 100, 117, 100);
                break;
            case 5:
                setIntRect(119, 100, 119, 100);
                break;
            case 6:
                setIntRect(238, 100, 125, 100);
                break;
            case 7:
                setIntRect(357 + 7, 100, 119, 100);
                break;
            }
        }

        animationTimer = 0.0f;
    }

    healthBar.setPosition(Vector2f(sprite.getPosition().x, sprite.getPosition().y - 20.f));
    healthBar.update(Health, MaxHealth);
}

void Pet::draw(RenderWindow &window, bool health = false)
{
    window.draw(sprite);
    if (!health)
    {
        return;
    }
    healthBar.setPosition({sprite.getPosition().x + 20, sprite.getPosition().y - 20});
    healthBar.draw(window);
}

int Pet::getAttack() const { return Attack; }
int Pet::getDefence() const { return Defence; }
int Pet::getHealth() const { return Health; }

// --- Dragon ---
Dragon::Dragon(std::string path, float startX, float startY, float scaleX, float scaleY, int totalFrames)
    : Pet(path, startX, startY, scaleX, scaleY, totalFrames, "Dragon")
{
    Health = 150;
    MaxHealth = 150;
    Attack = 30;
    Defence = 25;
}

void Dragon::useAbility()
{
    increaseAttack(10); // Dragon gets +10 Attack
}

// --- Griffin ---
Griffin::Griffin(std::string path, float startX, float startY, float scaleX, float scaleY, int totalFrames)
    : Pet(path, startX, startY, scaleX, scaleY, totalFrames, "Griffin")
{
    Health = 120;
    MaxHealth = 120;
    Attack = 25;
    Defence = 15;
}

void Griffin::useAbility()
{
    increaseAttack(5);  // +5 Attack
    increaseDefence(5); // +5 Defence
}

// --- Phoenix ---
Phoenix::Phoenix(std::string path, float startX, float startY, float scaleX, float scaleY, int totalFrames)
    : Pet(path, startX, startY, scaleX, scaleY, totalFrames, "Phoenix")
{
    Health = 110;
    MaxHealth = 110;
    Attack = 20;
    Defence = 10;
}

void Phoenix::useAbility()
{
    increaseHealth(5); // +5 Health
    increaseAttack(5); // +5 Attack
}

// --- Unicorn ---
Unicorn::Unicorn(std::string path, float startX, float startY, float scaleX, float scaleY, int totalFrames)
    : Pet(path, startX, startY, scaleX, scaleY, totalFrames, "Unicorn")
{
    Health = 130;
    MaxHealth = 130;
    Attack = 22;
    Defence = 18;
}

void Unicorn::useAbility()
{
    increaseHealth(30); // +30 Health
}


void Pet::setAttack(int value) { Attack = value; }
void Pet::setDefence(int value) { Defence = value; }
void Pet::setHealth(int value) { Health = value; }
void Pet::setLevel(int value) { level = value; }