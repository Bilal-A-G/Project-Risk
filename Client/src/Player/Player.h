#pragma once
#include <vector>

class Territory;
#include "../Territories/Territories.h"

class Player
{
public:
    bool isTurn;
    int numTerrCrtl;
    std::vector<Territory*> territories;

    
    void Reinforcement();
    void Attack();
    void Fortificate();
    
};
