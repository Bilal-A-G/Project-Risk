#include "Territories.h"

void Territory::Draw(Shader shader)
{
	if (playerInControl != -1)
	{
		meshRepresentation.SetTexture(playerInControl == 0 ? player0Occupied : player1Occupied);
	}

	meshRepresentation.Draw(shader);
}