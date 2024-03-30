#pragma once
#include <vector>

class Player
{
public:
    Player(int undeployedArmies) : isTurn(false), undeployedArmies(undeployedArmies), territoryCount(0){}
    
    void Reinforce();
    void Attack();
    void Fortify();
public:
    bool isTurn;
    int undeployedArmies;
    int territoryCount;
};
