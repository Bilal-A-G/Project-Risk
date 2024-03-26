#pragma once
#include <vector>
<<<<<<< Updated upstream

class Territory;
=======
#include "../Territories/Territories.h"
>>>>>>> Stashed changes

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
