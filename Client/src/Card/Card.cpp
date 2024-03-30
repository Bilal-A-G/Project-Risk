#include "Card.h"

int numExchanges = 1;

int Card::Exchange(std::vector<Card*> cards)
{
	int numArtillery = 0;
	int numCalvalry = 0;
	int numInfantry = 0;

	std::vector<Card*> artilleryCards;
	std::vector<Card*> calvalryCards;
	std::vector<Card*> infantryCards;


	for (int i = 0; i < cards.size(); i++)
	{
		if(cards[i]->type == CardType::INFANTRY)
		{
			infantryCards.push_back(cards[i]);
		}
		if (cards[i]->type == CardType::CALVALRY)
		{
			calvalryCards.push_back(cards[i]);
		}
		if (cards[i]->type == CardType::ARTILLERY)
		{
			artilleryCards.push_back(cards[i]);
		}
	}

	if(numArtillery >= 3)
	{
		artilleryCards.clear();
		return numExhanges * 5;
	}
	if (numInfantry >= 3)
	{
		infantryCards.clear();
		return numExhanges * 5;
	}
	if (numCalvalry >= 3)
	{
		calvalryCards.clear();
		return numExhanges * 5;
	}

	if(numArtillery >= 1 && numCalvalry >= 1 && numInfantry >= 1)
	{
		artilleryCards.clear();
		infantryCards.clear();
		calvalryCards.clear();
		return numExhanges * 5;
	}
}