#pragma once

enum CardType 
{
	INFANTRY = 0,
	ARTILLERY = 1,
	CALVALRY = 2
};

class Card
{
public:
	CardType type;
	static int Exchange(std::vector<Card*> cards);
};

