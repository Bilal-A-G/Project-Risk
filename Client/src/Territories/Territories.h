#pragma once
#include <vector>
#include <string>
#include "Mesh/Mesh.h"
#include "Shader/Shader.h"

const std::string player1Occupied = "Player1Occupied";
const std::string player0Occupied = "Player0Occupied";

class Territory 
{
public:
	Territory(std::string name, Mesh meshRepresentation) : 
		adjacentTerritories(std::vector<Territory*>()), name(name), playerInControl(-1), meshRepresentation(meshRepresentation) 
	{}

	void SetAdjacency(std::vector<Territory*> adjacencies) { adjacentTerritories = adjacencies; }
	void SetPlayerInControl(int player) { playerInControl = player; }
	void Draw(Shader shader);
private:
	std::vector<Territory*> adjacentTerritories;
	std::string name;
	int playerInControl;
	Mesh meshRepresentation;
};