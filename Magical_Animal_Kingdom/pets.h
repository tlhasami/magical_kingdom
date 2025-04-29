#pragma once
#include "object.h"
#include "HealthBar.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;

class Pet : public Object
{
protected:

    int MaxHealth;

    int Health;
    int Defence;
    int Attack;
    
    int TotalFrames;
    int currentFrame;
    
    float animationTimer;
    
    std::string petName;
    
    HealthBar healthBar;

    int level;
public:

    Pet(std::string path, float startX, float startY, float scaleX, float scaleY, int totalFrames, const std::string& name);

    void takeDamage(int amount);
    void increaseAttack(int amount);
    void increaseDefence(int amount);
    void increaseHealth(int amount);
    bool isAlive() const;

    void increaseLevel( int up  );

    void draw(RenderWindow& window , bool );
    int getAttack() const;
    int getDefence() const;
    int getHealth() const;
    int getLevel() const;

    void setAttack(int value) ;
    void setDefence(int value) ;
    void setHealth(int value);
    void setLevel(int value) ;

    void addHealth(int val);
    void addDefence(int val);
    void addAttack(int val);

    

    virtual void useAbility() = 0; // Every pet must override this
};

class Dragon : public Pet
{
public:
    Dragon(std::string path, float startX, float startY, float scaleX, float scaleY, int totalFrames);
    void useAbility() override; // Dragon special ability
    void updateAnimation(float deltaTime);
};

class Griffin : public Pet
{
public:
    Griffin(std::string path, float startX, float startY, float scaleX, float scaleY, int totalFrames);
    void useAbility() override; // Griffin special ability
    void updateAnimation(float deltaTime);
};

class Phoenix : public Pet
{
public:
    Phoenix(std::string path, float startX, float startY, float scaleX, float scaleY, int totalFrames);
    void useAbility() override; // Phoenix special ability
    void updateAnimation(float deltaTime);
};

class Unicorn : public Pet
{
public:
    Unicorn(std::string path, float startX, float startY, float scaleX, float scaleY, int totalFrames);
    void useAbility() override; // Unicorn special ability
    void updateAnimation(float deltaTime);
};
