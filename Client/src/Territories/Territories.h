#pragma once
#include <vector>
#include <string>
#include "Mesh/Mesh.h"
#include "Shader/Shader.h"

const std::string player1Occupied = "Player1Occupied";
const std::string player0Occupied = "Player0Occupied";

class Territory;

class Continent 
{
public:
	Continent(std::vector<Territory*> territories, int armyBonus) : territories(territories), armyBonus(armyBonus){}
	std::vector<Territory*> territories;
	int armyBonus;
};

class Territory 
{
public:
	Territory(std::string name, Mesh meshRepresentation) : 
		adjacentTerritories(std::vector<Territory*>()), name(name), playerInControl(-1), meshRepresentation(meshRepresentation) 
	{}

	void SetAdjacency(std::vector<Territory*> adjacencies) { adjacentTerritories = adjacencies; }
	void Draw(Shader shader);
private:
	Mesh meshRepresentation;
public:
	int numArmies;
	std::string name;
	int playerInControl;
	std::vector<Territory*> adjacentTerritories;
};