#pragma once
#include <vector>
#include <string>

using namespace std;

class Regions
{
	public:
		string name;
		int numOfArmies = 0;
		int playerInControl;

		vector<Regions*> adjacentRegions;
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