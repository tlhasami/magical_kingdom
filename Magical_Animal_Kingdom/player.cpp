// player.cpp
#include "player.h"

// ----------------- items class -------------------

items::items()
    : t_1(0), t_2(0), t_3(0), t_4(0), t_5(0), t_6(0), gems(100)
{
}

// Setters
void items::setT1(int value) { t_1 = value; }
void items::setT2(int value) { t_2 = value; }
void items::setT3(int value) { t_3 = value; }
void items::setT4(int value) { t_4 = value; }
void items::setT5(int value) { t_5 = value; }
void items::setT6(int value) { t_6 = value; }
void items::setGems(int value) { gems = value; }

// Adder

void items::addT1(int val){
    t_1 += val;
}
void items::addT2(int val){
    t_2 += val;
}
void items::addT3(int val){
    t_3 += val;
}
void items::addT4(int val){
    t_4 += val;
}
void items::addT5(int val){
    t_5 += val;
}
void items::addT6(int val){
    t_6 += val;
}

void items::addGems(int val){
    gems += val;
}

// Getters
int items::getT1() const { return t_1; }
int items::getT2() const { return t_2; }
int items::getT3() const { return t_3; }
int items::getT4() const { return t_4; }
int items::getT5() const { return t_5; }
int items::getT6() const { return t_6; }
int items::getGems() const { return gems; }

// ----------------- Player class -------------------

Player::Player(const std::string &playerName)
    : name(playerName),
      griffin("griffin.png", 450, 100, 1.5f, 1.5f, 9),
      dragon("dragon.png", 450, 350, 1.5f, 1.5f, 8),
      phoenix("phoniex.png", 700, 100, 0.5f, 0.5f, 8),
      unicorn("unicorn.png", 700, 350, 1.5f, 1.5f, 8)
{
    // Set initial frame of Pets
    dragon.setIntRect(0, 0, 75, 90);
    griffin.setIntRect(2, 0, 72, 90);
    phoenix.setIntRect(0, 50, 400, 200);
    unicorn.setIntRect(0, 121, 500 / 8, 121);
}

void Player::setPostionsDefault(){
    
    griffin.changePosition({ 450, 100});
    dragon.changePosition({450, 350});
    phoenix.changePosition({700, 100});
    unicorn.changePosition({700, 350});  
    
    griffin.changeScale({1.5f,1.5f});
    dragon.changeScale({1.5f,1.5f});
    phoenix.changeScale({0.5f , 0.5f});
    unicorn.changeScale({1.5f,1.5f});
}

void Player::setPostionTraining(){
    griffin.changePosition({60, 60});
    dragon.changePosition({60, 310});
    phoenix.changePosition({500, 60});
    unicorn.changePosition({540, 310});  

    griffin.changeScale({1.5f,1.5f});
    dragon.changeScale({1.5f,1.5f});
    phoenix.changeScale({0.5f , 0.5f});
    unicorn.changeScale({1.5f,1.5f});

}
// Setters
void Player::setName(const std::string &playerName)
{
    name = playerName;
}

string Player::getName() const {
    return name;
}