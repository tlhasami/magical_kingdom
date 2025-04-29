// player.h
#pragma once

#include <string>
#include "pets.h"

class items {
protected:
    int t_1;
    int t_2;
    int t_3;
    int t_4;
    int t_5;
    int t_6;
    int gems;

public:
    items(); // Constructor

    // Setters
    void setT1(int value);
    void setT2(int value);
    void setT3(int value);
    void setT4(int value);
    void setT5(int value);
    void setT6(int value);
    void setGems(int value);

    void addT1(int val);
    void addT2(int val);
    void addT3(int val);
    void addT4(int val);
    void addT5(int val);
    void addT6(int val);

    void addGems(int val);
    

    // Getters
    int getT1() const;
    int getT2() const;
    int getT3() const;
    int getT4() const;
    int getT5() const;
    int getT6() const;
    int getGems() const;
};

class Player : public items {
public:
    std::string name;
    Griffin griffin;
    Dragon dragon;
    Phoenix phoenix;
    Unicorn unicorn;

    Player(const std::string& playerName);

    // Setters
    void setName(const std::string& playerName);
    string getName() const ;

    void setPostionsDefault();
    void setPostionTraining();



};
