#pragma once
#include <vector>
#include <string>

using namespace std;

class Territory;

class Regions
{
	public:
		string name;
		int numOfArmies = 0;
		int playerInControl;

		Territory* ownedTerritory;
		vector<Regions*> adjacentRegions;

		Territory* returnOwnedTerritory()
		{
			return ownedTerritory;
		}

		void SetOwnedTerritory(Territory* inputTerritory)
		{
			ownedTerritory = inputTerritory;
		}
};

class Territory 
{
	public:
		vector<Regions*> regions;
		vector<Territory*> adjacentTerritories;
		string name;
		int controlValue;
		int playerInControl;
};