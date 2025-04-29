#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#include "player.h"
#include "button.h"

extern Vector2f screenResolution ;

class Training {
private:
    static char arr[12][25];
public:
    static int training(RenderWindow &window, Player &player, const int selection);
    
};
