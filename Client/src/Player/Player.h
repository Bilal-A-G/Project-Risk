#pragma once
#include <vector>

class Territory;

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
