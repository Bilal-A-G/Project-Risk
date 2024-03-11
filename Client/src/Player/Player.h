#pragma once
#include <vector>
#include "Territories.h"

class Player
{
public:
    bool isTurn;
    int numTerrCrtl;
    int numOfArmies;
    std::vector<Territory*> territories;
    
    void Reinforcement();

    void Attack();

    void Fortificate();
};
