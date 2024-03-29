#include <vector>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Camera/Camera.h"

#include "Core/main.cpp"
#include "iostream"
#include "glm/glm.hpp"
#include "Window/Window.h"
#include "IO/FileReader.h"
#include "Mesh/Mesh.h"
#include "Shader/Shader.h"
#include "Player/Player.cpp"
#include "Territories/Territories.cpp"


using namespace std;

Window* mainWindow;
Shader shader;

Mesh map;

Camera camera;

float height = 500;
float width = 500;

void CreateBoard();
void TerritorySetup();
vector<Player*> players;
vector<Territory*> territories;

Territory* NorthAmerica = new Territory();
Territory* SouthAmerica = new Territory();
Territory* Africa = new Territory();
Territory* Europe = new Territory();
Territory* Oceania = new Territory();
Territory* Asia = new Territory();

int playerCount = 0;
int playerTurn = 0;

bool onePicked = false;
bool twoPicked = false;
bool threePicked = false;
bool fourPicked = false;
bool fivePicked = false;
bool sixPicked = false;
bool boardIsLoaded = false;
bool hasEnoughArmies = false;
bool skippedAttackPhase = false;

int countryCount;
int diceNum;
int attackerDiceRolls;
int defenderDiceRolls;
int numOfArmies;
int numOfArmiesChosen;
int enemyRegionsAround = 0;
string chosenRegion;

Regions* defendingRegion;
Regions* attackingRegion;

Territory* TerritoryToRemoveFrom;

std::vector<Mesh> territoryMeshes;

void SetUpTerritories(std::vector<float> bufferData, std::vector<int> indices) 
{
	glm::mat4 territoryEmptyScale = glm::scale(glm::mat4(1), glm::vec3(0.015f, 0.03f, 0.03f));

	//North America Territories
	Mesh alaska = Mesh();
	alaska.Create(bufferData, indices, "BlankTile");
	alaska.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-60.0f, 23.0f, 0.0f)));
	territoryMeshes.push_back(alaska);

	Mesh nwTerritories = Mesh();
	nwTerritories.Create(bufferData, indices, "BlankTile");
	nwTerritories.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-50.0f, 23.0f, 0.0f)));
	territoryMeshes.push_back(nwTerritories);

	Mesh alberta = Mesh();
	alberta.Create(bufferData, indices, "BlankTile");
	alberta.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-50.0f, 17.0f, 0.0f)));
	territoryMeshes.push_back(alberta);

	Mesh ontario = Mesh();
	ontario.Create(bufferData, indices, "BlankTile");
	ontario.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-43.0f, 17.0f, 0.0f)));
	territoryMeshes.push_back(ontario);

	Mesh quebec = Mesh();
	quebec.Create(bufferData, indices, "BlankTile");
	quebec.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-35.0f, 15.0f, 0.0f)));
	territoryMeshes.push_back(quebec);

	Mesh westernUS = Mesh();
	westernUS.Create(bufferData, indices, "BlankTile");
	westernUS.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-50.0f, 10.0f, 0.0f)));
	territoryMeshes.push_back(westernUS);

	Mesh easternUS = Mesh();
	easternUS.Create(bufferData, indices, "BlankTile");
	easternUS.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-40.0f, 8.0f, 0.0f)));
	territoryMeshes.push_back(easternUS);

	Mesh centralAmerica = Mesh();
	centralAmerica.Create(bufferData, indices, "BlankTile");
	centralAmerica.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-47.0f, 1.0f, 0.0f)));
	territoryMeshes.push_back(centralAmerica);

	Mesh greenland = Mesh();
	greenland.Create(bufferData, indices, "BlankTile");
	greenland.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-28.0f, 25.0f, 0.0f)));
	territoryMeshes.push_back(greenland);

	//South America Territories
	Mesh venezuela = Mesh();
	venezuela.Create(bufferData, indices, "BlankTile");
	venezuela.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-40.0f, -5.0f, 0.0f)));
	territoryMeshes.push_back(venezuela);

	Mesh peru = Mesh();
	peru.Create(bufferData, indices, "BlankTile");
	peru.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-40.0f, -13.0f, 0.0f)));
	territoryMeshes.push_back(peru);

	Mesh brazil = Mesh();
	brazil.Create(bufferData, indices, "BlankTile");
	brazil.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-30.0f, -13.0f, 0.0f)));
	territoryMeshes.push_back(brazil);

	Mesh argentina = Mesh();
	argentina.Create(bufferData, indices, "BlankTile");
	argentina.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-37.0f, -20.0f, 0.0f)));
	territoryMeshes.push_back(argentina);

	//Europe Territories
	Mesh uk = Mesh();
	uk.Create(bufferData, indices, "BlankTile");
	uk.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-18.0f, 11.0f, 0.0f)));
	territoryMeshes.push_back(uk);

	Mesh westernEU = Mesh();
	westernEU.Create(bufferData, indices, "BlankTile");
	westernEU.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-18.0f, 2.0f, 0.0f)));
	territoryMeshes.push_back(westernEU);

	Mesh southernEU = Mesh();
	southernEU.Create(bufferData, indices, "BlankTile");
	southernEU.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-8.0f, 5.0f, 0.0f)));
	territoryMeshes.push_back(southernEU);

	Mesh northernEU = Mesh();
	northernEU.Create(bufferData, indices, "BlankTile");
	northernEU.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-8.0f, 11.0f, 0.0f)));
	territoryMeshes.push_back(northernEU);

	Mesh ukraine = Mesh();
	ukraine.Create(bufferData, indices, "BlankTile");
	ukraine.SetModel(glm::translate(territoryEmptyScale, glm::vec3(2.0f, 15.0f, 0.0f)));
	territoryMeshes.push_back(ukraine);

	Mesh scandinavia = Mesh();
	scandinavia.Create(bufferData, indices, "BlankTile");
	scandinavia.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-8.0f, 20.0f, 0.0f)));
	territoryMeshes.push_back(scandinavia);

	Mesh iceland = Mesh();
	iceland.Create(bufferData, indices, "BlankTile");
	iceland.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-17.0f, 20.0f, 0.0f)));
	territoryMeshes.push_back(iceland);

	//Africa Territories
	Mesh northAfrica = Mesh();
	northAfrica.Create(bufferData, indices, "BlankTile");
	northAfrica.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-10.0f, -8.0f, 0.0f)));
	territoryMeshes.push_back(northAfrica);

	Mesh egypt = Mesh();
	egypt.Create(bufferData, indices, "BlankTile");
	egypt.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-2.0f, -6.0f, 0.0f)));
	territoryMeshes.push_back(egypt);

	Mesh eastAfrica = Mesh();
	eastAfrica.Create(bufferData, indices, "BlankTile");
	eastAfrica.SetModel(glm::translate(territoryEmptyScale, glm::vec3(3.0f, -15.0f, 0.0f)));
	territoryMeshes.push_back(eastAfrica);

	Mesh congo = Mesh();
	congo.Create(bufferData, indices, "BlankTile");
	congo.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-3.0f, -18.0f, 0.0f)));
	territoryMeshes.push_back(congo);

	Mesh southAfrica = Mesh();
	southAfrica.Create(bufferData, indices, "BlankTile");
	southAfrica.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-3.0f, -26.0f, 0.0f)));
	territoryMeshes.push_back(southAfrica);

	Mesh madagascar = Mesh();
	madagascar.Create(bufferData, indices, "BlankTile");
	madagascar.SetModel(glm::translate(territoryEmptyScale, glm::vec3(8.0f, -26.0f, 0.0f)));
	territoryMeshes.push_back(madagascar);

	//Asia Territories
	Mesh middleEast = Mesh();
	middleEast.Create(bufferData, indices, "BlankTile");
	middleEast.SetModel(glm::translate(territoryEmptyScale, glm::vec3(4.0f, 0.0f, 0.0f)));
	territoryMeshes.push_back(middleEast);

	Mesh india = Mesh();
	india.Create(bufferData, indices, "BlankTile");
	india.SetModel(glm::translate(territoryEmptyScale, glm::vec3(18.0f, -2.0f, 0.0f)));
	territoryMeshes.push_back(india);

	Mesh siam = Mesh();
	siam.Create(bufferData, indices, "BlankTile");
	siam.SetModel(glm::translate(territoryEmptyScale, glm::vec3(30.0f, -5.0f, 0.0f)));
	territoryMeshes.push_back(siam);

	Mesh china = Mesh();
	china.Create(bufferData, indices, "BlankTile");
	china.SetModel(glm::translate(territoryEmptyScale, glm::vec3(30.0f, 2.0f, 0.0f)));
	territoryMeshes.push_back(china);

	Mesh mongolia = Mesh();
	mongolia.Create(bufferData, indices, "BlankTile");
	mongolia.SetModel(glm::translate(territoryEmptyScale, glm::vec3(30.0f, 10.0f, 0.0f)));
	territoryMeshes.push_back(mongolia);

	Mesh irkutsk = Mesh();
	irkutsk.Create(bufferData, indices, "BlankTile");
	irkutsk.SetModel(glm::translate(territoryEmptyScale, glm::vec3(30.0f, 18.0f, 0.0f)));
	territoryMeshes.push_back(irkutsk);

	Mesh yakutsk = Mesh();
	yakutsk.Create(bufferData, indices, "BlankTile");
	yakutsk.SetModel(glm::translate(territoryEmptyScale, glm::vec3(30.0f, 25.0f, 0.0f)));
	territoryMeshes.push_back(yakutsk);

	Mesh kamchatka = Mesh();
	kamchatka.Create(bufferData, indices, "BlankTile");
	kamchatka.SetModel(glm::translate(territoryEmptyScale, glm::vec3(40.0f, 25.0f, 0.0f)));
	territoryMeshes.push_back(kamchatka);

	Mesh siberia = Mesh();
	siberia.Create(bufferData, indices, "BlankTile");
	siberia.SetModel(glm::translate(territoryEmptyScale, glm::vec3(20.0f, 22.0f, 0.0f)));
	territoryMeshes.push_back(siberia);

	Mesh ural = Mesh();
	ural.Create(bufferData, indices, "BlankTile");
	ural.SetModel(glm::translate(territoryEmptyScale, glm::vec3(15.0f, 16.0f, 0.0f)));
	territoryMeshes.push_back(ural);

	Mesh afghanistan = Mesh();
	afghanistan.Create(bufferData, indices, "BlankTile");
	afghanistan.SetModel(glm::translate(territoryEmptyScale, glm::vec3(13.0f, 9.0f, 0.0f)));
	territoryMeshes.push_back(afghanistan);

	Mesh japan = Mesh();
	japan.Create(bufferData, indices, "BlankTile");
	japan.SetModel(glm::translate(territoryEmptyScale, glm::vec3(43.0f, 10.0f, 0.0f)));
	territoryMeshes.push_back(japan);

	//Oceania Territories
	Mesh indonesia = Mesh();
	indonesia.Create(bufferData, indices, "BlankTile");
	indonesia.SetModel(glm::translate(territoryEmptyScale, glm::vec3(31.0f, -16.0f, 0.0f)));
	territoryMeshes.push_back(indonesia);

	Mesh westernAU = Mesh();
	westernAU.Create(bufferData, indices, "BlankTile");
	westernAU.SetModel(glm::translate(territoryEmptyScale, glm::vec3(37.0f, -26.0f, 0.0f)));
	territoryMeshes.push_back(westernAU);

	Mesh easternAU = Mesh();
	easternAU.Create(bufferData, indices, "BlankTile");
	easternAU.SetModel(glm::translate(territoryEmptyScale, glm::vec3(46.0f, -25.0f, 0.0f)));
	territoryMeshes.push_back(easternAU);

	Mesh newGuinea = Mesh();
	newGuinea.Create(bufferData, indices, "BlankTile");
	newGuinea.SetModel(glm::translate(territoryEmptyScale, glm::vec3(42.0f, -14.0f, 0.0f)));
	territoryMeshes.push_back(newGuinea);
}

void CreateBoard()
{
	mainWindow = new Window(width, height, "Window");
	mainWindow->SetClearColour(0.0f, 0.0f, 0.0f, 1.0f);

	std::vector<char> fragSource = FileReader::ReadFile("Fragment");
	std::vector<char> vertSource = FileReader::ReadFile("Vertex");

	shader.Compile(vertSource, ShaderType::VERTEX);
	shader.Compile(fragSource, ShaderType::FRAGMENT);

	shader.Link();

	territoryMeshes = std::vector<Mesh>();

	std::vector<float> bufferData =
	{
		-1.0f, -1.0f, 0.0f, 0, 1,
		-1.0f, 1.0f, 0.0f, 0, 0,
		1.0f, -1.0f, 0.0f, 1, 1,
		1.0f, 1.0f, 0.0f, 1, 0
	};

	std::vector<int> indices =
	{
		0, 1, 2,
		3, 1, 2,
	};

	map.Create(bufferData, indices, "map");
	SetUpTerritories(bufferData, indices);

	boardIsLoaded = true;
}

void Start()
{
	TerritorySetup();
	
	/* testing territory setup
	
	for (Territory* i : territories)
	{
		for (Regions* j : i->regions)
		{
			cout << j->name << '\n';
		}
	}
	
	*/

	cout << "Please write a number of players between 2 to 4: \n";
	cin >> playerCount;

	if (playerCount < 2)
	{
		playerCount = 2;
	}
	else if (playerCount > 4)
	{
		playerCount = 4;
	}

	for (int i = 1; i <= playerCount; ++i)
	{
		players.push_back(new Player());
	}

	for (int i = 1; i <= players.size(); ++i)
	{
		int territoryNum = rand() % 6 + 1;

		switch (territoryNum)
		{
			case 1:
				if (onePicked == false)
				{
					for (Territory* j : territories)
					{
						if (j->name == "NorthAmerica")
						{
							j->playerInControl = i;
							players[i - 1]->territories.insert(players[i - 1]->territories.end(), {NorthAmerica});
						}
					}

					onePicked = true; // makes sure nortAmerica doesn't get assigned to more than one person
				}
				else
				{
					i--; // if the number was already picked, reset i so that it doesn't skip over the player and assigns a new number
					break;
				}
				break;
			case 2:
				if (twoPicked == false)
				{
					for (Territory* j : territories)
					{
						if (j->name == "SouthAmerica")
						{
							j->playerInControl = i;
							players[i - 1]->territories.insert(players[i - 1]->territories.end(), {SouthAmerica});
						}
					}
					twoPicked = true; // makes sure southAmerica doesn't get assigned to more than one person
				}
				else
				{
					i--; // if the number was already picked, reset i so that it doesn't skip over the player and assigns a new number
					break;
				}
				break;
			case 3:
				if (threePicked == false)
				{
					for (Territory* j : territories)
					{
						if (j->name == "Europe")
						{
							j->playerInControl = i;
							players[i - 1]->territories.insert(players[i - 1]->territories.end(), {Europe});
						}
					}
					threePicked = true; // makes sure eurasia doesn't get assigned to more than one person
				}
				else
				{
					i--; // if the number was already picked, reset i so that it doesn't skip over the player and assigns a new number
					break;
				}
				break;
			case 4:
				if (fourPicked == false)
				{
					for (Territory* j : territories)
					{
						if (j->name == "Asia")
						{
							j->playerInControl = i;
							players[i - 1]->territories.insert(players[i - 1]->territories.end(), {Asia});
						}
					}
					fourPicked = true; // makes sure africa doesn't get assigned to more than one person
				}
				else
				{
					i--; // if the number was already picked, reset i so that it doesn't skip over the player and assigns a new number
					break;
				}
				break;
			case 5:
				if (fivePicked == false)
				{
					for (Territory* j : territories)
					{
						if (j->name == "Oceania")
						{
							j->playerInControl = i;
							players[i - 1]->territories.insert(players[i - 1]->territories.end(), {Oceania});
						}
					}
					fivePicked = true; // makes sure africa doesn't get assigned to more than one person
				}
				else
				{
					i--; // if the number was already picked, reset i so that it doesn't skip over the player and assigns a new number
					break;
				}
				break;
			case 6:
				if (sixPicked == false)
				{
					for (Territory* j : territories)
					{
						if (j->name == "Africa")
						{
							j->playerInControl = i;
							players[i - 1]->territories.insert(players[i - 1]->territories.end(), {Africa});
						}
					}
					sixPicked = true; // makes sure africa doesn't get assigned to more than one person
				}
				else
				{
					i--; // if the number was already picked, reset i so that it doesn't skip over the player and assigns a new number
					break;
				}
				break;
		}
	}

	//for (Territory* i : territories)
	//{
	//	cout << i->playerInControl << '\n';
	//}

	CreateBoard();
}

void Update() 
{
	mainWindow->Update();
	App::isRunning = !mainWindow->GetWindowShouldClose();

	//glm::mat4 perspective = glm::perspective(90.0f, (float)mainWindow->width / (float)mainWindow->height, 0.01f, 100.0f);
	//perspective = glm::rotate(perspective, -6.86f, glm::vec3(1.0f, 0.0f, 0.0f));
	//map.SetProjection(perspective);
	map.Draw(shader);
	for (int i = 0; i < territoryMeshes.size(); i++)
	{
		territoryMeshes[i].Draw(shader);
	}

	//camera.Update(view, *mainWindow);

	if (boardIsLoaded == true)
	{
		switch (playerTurn)
		{
			case 0: // player 1 turn
				cout << "\nPlayer 1's Turn.\n";
				players[0]->Reinforcement();
				players[0]->Attack();

				if (skippedAttackPhase == true)
				{
					players[0]->Fortificate();
				}

				playerTurn = 1; // set to player 2 turn

				break;
			case 1: // player 2 turn
				cout << "\nPlayer 2's Turn.\n";
				players[1]->Reinforcement();
				players[1]->Attack();
				
				if (skippedAttackPhase == true)
				{
					players[1]->Fortificate();
				}

				if (playerCount > 2)
				{
					playerTurn = 2; // set to player 3 turn
				}
				else
				{
					playerTurn = 0; // set to player 1 turn if there is no player 3
				}

				break;
			case 2: // player 3 turn
				cout << "\nPlayer 3's Turn.\n";
				players[2]->Reinforcement();
				players[2]->Attack();
				
				if (skippedAttackPhase == true)
				{
					players[2]->Fortificate();
				}

				if (playerCount > 3)
				{
					playerTurn = 3; // set to player 4 turn
				}
				else
				{
					playerTurn = 0; // set to player 1 turn if there is no player 4
				}

				break;
			case 3: // player 4 turn
				cout << "\nPlayer 4's Turn.\n";
				players[3]->Reinforcement();
				players[3]->Attack();

				if (skippedAttackPhase == true)
				{
					players[3]->Fortificate();
				}

				playerTurn = 0; // set to player 1 turn
				break;
		}
	}
}

void TerritorySetup()
{
	// North America
	NorthAmerica->name = "NorthAmerica";
	Regions* Alaska = new Regions();
	Alaska->name = "Alaska";
	Alaska->SetOwnedTerritory(NorthAmerica);
	Regions* NorthwestTerritory = new Regions();
	NorthwestTerritory->name = "NorthwestTerritory";
	NorthwestTerritory->SetOwnedTerritory(NorthAmerica);
	Regions* Greenland = new Regions();
	Greenland->name = "Greenland";
	Greenland->SetOwnedTerritory(NorthAmerica);
	Regions* Alberta = new Regions();
	Alberta->name = "Alberta";
	Alberta->SetOwnedTerritory(NorthAmerica);
	Regions* Ontario = new Regions();
	Ontario->name = "Ontario";
	Ontario->SetOwnedTerritory(NorthAmerica);
	Regions* Quebec = new Regions();
	Quebec->name = "Quebec";
	Quebec->SetOwnedTerritory(NorthAmerica);
	Regions* WesternUnitedStates = new Regions();
	WesternUnitedStates->name = "WesternUnitedStates";
	WesternUnitedStates->SetOwnedTerritory(NorthAmerica);
	Regions* EasternUnitedStates = new Regions();
	EasternUnitedStates->name = "EasternUnitedStates";
	EasternUnitedStates->SetOwnedTerritory(NorthAmerica);
	Regions* CentralAmerica = new Regions();
	CentralAmerica->name = "CentralAmerica";
	CentralAmerica->SetOwnedTerritory(NorthAmerica);
	Regions* EasternCanada = new Regions();
	EasternCanada->name = "EasternCanada";
	EasternCanada->SetOwnedTerritory(NorthAmerica);

	NorthAmerica->regions.insert(NorthAmerica->regions.end(), 
		{Alaska, NorthwestTerritory, Greenland, Alberta, Ontario, Quebec, WesternUnitedStates, EasternUnitedStates, CentralAmerica, EasternCanada});

	for (Regions* k : NorthAmerica->regions)
	{
		k->playerInControl = NorthAmerica->playerInControl;
	}

	// South America
	SouthAmerica->name = "SouthAmerica";
	Regions* Venezuela = new Regions();
	Venezuela->name = "Venezuela";
	Venezuela->SetOwnedTerritory(SouthAmerica);
	Regions* Peru = new Regions();
	Peru->name = "Peru";
	Peru->SetOwnedTerritory(SouthAmerica);
	Regions* Brazil = new Regions();
	Brazil->name = "Brazil";
	Brazil->SetOwnedTerritory(SouthAmerica);
	Regions* Argentina = new Regions();
	Argentina->name = "Argentina";
	Argentina->SetOwnedTerritory(SouthAmerica);

	SouthAmerica->regions.insert(SouthAmerica->regions.end(),
		{Venezuela, Peru, Brazil, Argentina});

	for (Regions* k : SouthAmerica->regions)
	{
		k->playerInControl = SouthAmerica->playerInControl;
	}

	// Africa
	Africa->name = "Africa";
	Regions* NorthAfrica = new Regions();
	NorthAfrica->name = "NorthAfrica";
	NorthAfrica->SetOwnedTerritory(Africa);
	Regions* Egypt = new Regions();
	Egypt->name = "Egypt";
	Egypt->SetOwnedTerritory(Africa);
	Regions* EastAfrica = new Regions();
	EastAfrica->name = "EastAfrica";
	EastAfrica->SetOwnedTerritory(Africa);
	Regions* SouthAfrica = new Regions();
	SouthAfrica->name = "SouthAfrica";
	SouthAfrica->SetOwnedTerritory(Africa);
	Regions* Madagascar = new Regions();
	Madagascar->name = "Madagascar";
	Madagascar->SetOwnedTerritory(Africa);
	Regions* CentralAfrica = new Regions();
	CentralAfrica->name = "CentralAfrica";
	CentralAfrica->SetOwnedTerritory(Africa);

	Africa->regions.insert(Africa->regions.end(),
		{NorthAfrica, Egypt, EastAfrica, CentralAfrica, SouthAfrica, Madagascar});

	for (Regions* k : Africa->regions)
	{
		k->playerInControl = Africa->playerInControl;
	}

	// Europe
	Europe->name = "Europe";
	Regions* Iceland = new Regions();
	Iceland->name = "Iceland";
	Iceland->SetOwnedTerritory(Europe);
	Regions* Scandinavia = new Regions();
	Scandinavia->name = "Scandinavia";
	Scandinavia->SetOwnedTerritory(Europe);
	Regions* GreatBritain = new Regions();
	GreatBritain->name = "GreatBritain";
	GreatBritain->SetOwnedTerritory(Europe);
	Regions* NorthernEurope = new Regions();
	NorthernEurope->name = "NorthernEurope";
	NorthernEurope->SetOwnedTerritory(Europe);
	Regions* SouthernEurope = new Regions();
	SouthernEurope->name = "SouthernEurope";
	SouthernEurope->SetOwnedTerritory(Europe);
	Regions* WesternEurope = new Regions();
	WesternEurope->name = "WesternEurope";
	WesternEurope->SetOwnedTerritory(Europe);
	Regions* Russia = new Regions();
	Russia->name = "Russia";
	Russia->SetOwnedTerritory(Europe);

	Europe->regions.insert(Europe->regions.end(),
		{Iceland, Scandinavia, Russia, GreatBritain, NorthernEurope, SouthernEurope, WesternEurope});

	for (Regions* k : Europe->regions)
	{
		k->playerInControl = Europe->playerInControl;
	}

	// Oceania
	Oceania->name = "Oceania";
	Regions* Indonesia = new Regions();
	Indonesia->name = "Indonesia";
	Indonesia->SetOwnedTerritory(Oceania);
	Regions* NewGuinea = new Regions();
	NewGuinea->name = "NewGuinea";
	NewGuinea->SetOwnedTerritory(Oceania);
	Regions* WesternAustralia = new Regions();
	WesternAustralia->name = "WesternAustralia";
	WesternAustralia->SetOwnedTerritory(Oceania);
	Regions* EasternAustralia = new Regions();
	EasternAustralia->name = "EasternAustralia";
	EasternAustralia->SetOwnedTerritory(Oceania);

	Oceania->regions.insert(Oceania->regions.end(),
		{Indonesia, NewGuinea, WesternAustralia, EasternAustralia});

	for (Regions* k : Oceania->regions)
	{
		k->playerInControl = Oceania->playerInControl;
	}

	// Asia
	Asia->name = "Asia";
	Regions* Siam = new Regions();
	Siam->name = "Siam";
	Siam->SetOwnedTerritory(Asia);
	Regions* India = new Regions();
	India->name = "India";
	India->SetOwnedTerritory(Asia);
	Regions* China = new Regions();
	China->name = "China";
	China->SetOwnedTerritory(Asia);
	Regions* Mongolia = new Regions();
	Mongolia->name = "Mongolia";
	Mongolia->SetOwnedTerritory(Asia);
	Regions* Japan = new Regions();
	Japan->name = "Japan";
	Japan->SetOwnedTerritory(Asia);
	Regions* Irkutsk = new Regions();
	Irkutsk->name = "Irkutsk";
	Irkutsk->SetOwnedTerritory(Asia);
	Regions* Yakutsk = new Regions();
	Yakutsk->name = "Yakutsk";
	Yakutsk->SetOwnedTerritory(Asia);
	Regions* Kamchatka = new Regions();
	Kamchatka->name = "Kamchatka";
	Kamchatka->SetOwnedTerritory(Asia);
	Regions* Siberia = new Regions();
	Siberia->name = "Siberia";
	Siberia->SetOwnedTerritory(Asia);
	Regions* Afghanistan = new Regions();
	Afghanistan->name = "Afghanistan";
	Afghanistan->SetOwnedTerritory(Asia);
	Regions* Ural = new Regions();
	Ural->name = "Ural";
	Ural->SetOwnedTerritory(Asia);
	Regions* MiddleEast = new Regions();
	MiddleEast->name = "MiddleEast";
	MiddleEast->SetOwnedTerritory(Asia);
	Regions* SoutheastAsia = new Regions();
	SoutheastAsia->name = "SoutheastAsia";
	SoutheastAsia->SetOwnedTerritory(Asia);

	Asia->regions.insert(Asia->regions.end(),
		{Siam, India, China, Mongolia, Japan, Irkutsk, Yakutsk, Kamchatka, Siberia, Afghanistan, Ural, MiddleEast, SoutheastAsia});

	for (Regions* k : Asia->regions)
	{
		k->playerInControl = Asia->playerInControl;
	}

	// Adding Territories to Vector

	territories.insert(territories.end(), {NorthAmerica, SouthAmerica, Africa, Europe, Asia, Oceania});

	// North America Adjacents

	Greenland->adjacentRegions.insert(Greenland->adjacentRegions.end(),
		{ NorthwestTerritory, Ontario, EasternCanada, Iceland});

	Alaska->adjacentRegions.insert(Alaska->adjacentRegions.end(),
		{NorthwestTerritory, Alberta, Kamchatka});

	NorthwestTerritory->adjacentRegions.insert(NorthwestTerritory->adjacentRegions.end(),
		{Alaska, Alberta, Ontario, Greenland});

	Alberta->adjacentRegions.insert(Alberta->adjacentRegions.end(),
		{Alaska, NorthwestTerritory, Ontario, WesternUnitedStates});

	Ontario->adjacentRegions.insert(Ontario->adjacentRegions.end(),
		{NorthwestTerritory, Alberta, EasternCanada, WesternUnitedStates, EasternUnitedStates, Greenland});

	EasternCanada->adjacentRegions.insert(EasternCanada->adjacentRegions.end(),
		{Greenland, Ontario, EasternUnitedStates});

	WesternUnitedStates->adjacentRegions.insert(WesternUnitedStates->adjacentRegions.end(),
		{Alberta, Ontario, EasternUnitedStates, CentralAmerica});

	EasternUnitedStates->adjacentRegions.insert(EasternUnitedStates->adjacentRegions.end(),
		{WesternUnitedStates, CentralAmerica, Ontario, EasternCanada});

	CentralAmerica->adjacentRegions.insert(CentralAmerica->adjacentRegions.end(),
		{WesternUnitedStates, EasternUnitedStates, Venezuela});

	// South America Adjacents

	Venezuela->adjacentRegions.insert(Venezuela->adjacentRegions.end(),
		{CentralAmerica, Peru, Brazil});

	Peru->adjacentRegions.insert(Peru->adjacentRegions.end(),
		{Venezuela, Brazil, Argentina});

	Brazil->adjacentRegions.insert(Brazil->adjacentRegions.end(),
		{Venezuela, Peru, Argentina, NorthAfrica});

	Argentina->adjacentRegions.insert(Argentina->adjacentRegions.end(),
		{Peru, Brazil});

	// Europe Adjacents

	Iceland->adjacentRegions.insert(Iceland->adjacentRegions.end(),
		{Greenland, GreatBritain, Scandinavia});

	GreatBritain->adjacentRegions.insert(GreatBritain->adjacentRegions.end(),
		{Iceland, Scandinavia, NorthernEurope, WesternEurope});

	WesternEurope->adjacentRegions.insert(WesternEurope->adjacentRegions.end(),
		{GreatBritain, NorthernEurope, SouthernEurope, NorthAfrica});

	Scandinavia->adjacentRegions.insert(Scandinavia->adjacentRegions.end(),
		{Iceland, GreatBritain, NorthernEurope, Russia});

	NorthernEurope->adjacentRegions.insert(NorthernEurope->adjacentRegions.end(),
		{GreatBritain, Scandinavia, WesternEurope, SouthernEurope, Russia});

	SouthernEurope->adjacentRegions.insert(SouthernEurope->adjacentRegions.end(),
		{WesternEurope, NorthernEurope, Russia, MiddleEast, NorthAfrica, Egypt});

	Russia->adjacentRegions.insert(Russia->adjacentRegions.end(),
		{Scandinavia, NorthernEurope, SouthernEurope, MiddleEast, Ural, Afghanistan});

	// Africa Adjacents

	NorthAfrica->adjacentRegions.insert(NorthAfrica->adjacentRegions.end(),
		{Brazil, WesternEurope, SouthernEurope, Egypt, EastAfrica, CentralAfrica});

	Egypt->adjacentRegions.insert(Egypt->adjacentRegions.end(),
		{NorthAfrica, SouthernEurope, MiddleEast, EastAfrica});

	EastAfrica->adjacentRegions.insert(EastAfrica->adjacentRegions.end(),
		{NorthAfrica, Egypt, CentralAfrica, SouthAfrica, Madagascar, MiddleEast});

	CentralAfrica->adjacentRegions.insert(CentralAfrica->adjacentRegions.end(),
		{NorthAfrica, EastAfrica, SouthAfrica});

	SouthAfrica->adjacentRegions.insert(SouthAfrica->adjacentRegions.end(),
		{CentralAfrica, EastAfrica, Madagascar});

	Madagascar->adjacentRegions.insert(Madagascar->adjacentRegions.end(),
		{SouthAfrica, EastAfrica});

	// Asia Adjacents

	MiddleEast->adjacentRegions.insert(MiddleEast->adjacentRegions.end(),
		{SouthernEurope, Russia, Egypt, EastAfrica, Afghanistan, India});

	Afghanistan->adjacentRegions.insert(Afghanistan->adjacentRegions.end(),
		{Russia, MiddleEast, Ural, China, India});

	Ural->adjacentRegions.insert(Ural->adjacentRegions.end(),
		{Siberia, Russia, Afghanistan, China});

	Siberia->adjacentRegions.insert(Siberia->adjacentRegions.end(),
		{Ural, Yakutsk, Irkutsk, China, Mongolia});

	Yakutsk->adjacentRegions.insert(Yakutsk->adjacentRegions.end(),
		{Siberia, Kamchatka, Irkutsk});

	Kamchatka->adjacentRegions.insert(Kamchatka->adjacentRegions.end(),
		{Yakutsk, Irkutsk, Mongolia, Japan, Alaska});

	Irkutsk->adjacentRegions.insert(Irkutsk->adjacentRegions.end(),
		{Yakutsk, Siberia, Mongolia, Kamchatka});

	Mongolia->adjacentRegions.insert(Mongolia->adjacentRegions.end(),
		{Siberia, Irkutsk, Kamchatka, Japan, China});

	Japan->adjacentRegions.insert(Japan->adjacentRegions.end(),
		{Kamchatka, Mongolia});

	China->adjacentRegions.insert(China->adjacentRegions.end(),
		{SoutheastAsia, India, Afghanistan, Ural, Siberia, Mongolia});

	India->adjacentRegions.insert(India->adjacentRegions.end(),
		{MiddleEast, Afghanistan, China, SoutheastAsia});

	SoutheastAsia->adjacentRegions.insert(SoutheastAsia->adjacentRegions.end(),
		{India, China, Indonesia});

	// Oceania Adjacents

	Indonesia->adjacentRegions.insert(Indonesia->adjacentRegions.end(),
		{SoutheastAsia, NewGuinea, WesternAustralia});

	NewGuinea->adjacentRegions.insert(NewGuinea->adjacentRegions.end(),
		{Indonesia, EasternAustralia});

	WesternAustralia->adjacentRegions.insert(WesternAustralia->adjacentRegions.end(),
		{Indonesia, EasternAustralia});

	EasternAustralia->adjacentRegions.insert(EasternAustralia->adjacentRegions.end(),
		{WesternAustralia, NewGuinea});
}

void Player::Reinforcement()
{
	switch (playerTurn)
	{
		case 0:
			countryCount = 0;

			for (Territory* i : players[0]->territories)
			{
				for (Regions* j : i->regions)
				{
					countryCount++;
				}
			}

			players[0]->numOfArmies += floor(countryCount / 3);

			cout << "Choose which region you wish to assign your armies to: \n";

			for (Territory* i : players[0]->territories)
			{
				for (Regions* j : i->regions)
				{
					cout << j->name << '\n';
				}
			}

			cin >> chosenRegion;

			cout << "\nChoose a number of armies you wish to assign out of " << players[0]->numOfArmies << ": \n";

			cin >> numOfArmiesChosen;

			players[0]->numOfArmies -= numOfArmiesChosen;

			for (Territory* i : players[0]->territories)
			{
				for (Regions* j : i->regions)
				{
					if (j->name == chosenRegion)
					{
						j->numOfArmies += numOfArmiesChosen;
					}
				}
			}

			break;
		case 1:
			countryCount = 0;

			for (Territory* i : players[1]->territories)
			{
				for (Regions* j : i->regions)
				{
					countryCount++;
				}
			}

			players[1]->numOfArmies += floor(countryCount / 3);

			cout << "Choose which region you wish to assign your armies to: \n";

			for (Territory* i : players[1]->territories)
			{
				for (Regions* j : i->regions)
				{
					cout << j->name << '\n';
				}
			}

			cin >> chosenRegion;

			cout << "\nChoose a number of armies you wish to assign out of " << players[1]->numOfArmies << ": \n";

			cin >> numOfArmiesChosen;

			players[1]->numOfArmies -= numOfArmiesChosen;

			for (Territory* i : players[1]->territories)
			{
				for (Regions* j : i->regions)
				{
					if (j->name == chosenRegion)
					{
						j->numOfArmies += numOfArmiesChosen;
					}
				}
			}
			break;
		case 2:
			countryCount = 0;

			for (Territory* i : players[2]->territories)
			{
				for (Regions* j : i->regions)
				{
					countryCount++;
				}
			}

			players[2]->numOfArmies += floor(countryCount / 3);

			cout << "Choose which region you wish to assign your armies to: \n";

			for (Territory* i : players[2]->territories)
			{
				for (Regions* j : i->regions)
				{
					cout << j->name << '\n';
				}
			}

			cin >> chosenRegion;

			cout << "\nChoose a number of armies you wish to assign out of " << players[2]->numOfArmies << ": \n";

			cin >> numOfArmiesChosen;

			players[2]->numOfArmies -= numOfArmiesChosen;

			for (Territory* i : players[2]->territories)
			{
				for (Regions* j : i->regions)
				{
					if (j->name == chosenRegion)
					{
						j->numOfArmies += numOfArmiesChosen;
					}
				}
			}
			break;
		case 3:
			countryCount = 0;

			for (Territory* i : players[3]->territories)
			{
				for (Regions* j : i->regions)
				{
					countryCount++;
				}
			}

			players[3]->numOfArmies += floor(countryCount / 3);

			cout << "Choose which region you wish to assign your armies to: \n";

			for (Territory* i : players[3]->territories)
			{
				for (Regions* j : i->regions)
				{
					cout << j->name << '\n';
				}
			}

			cin >> chosenRegion;

			cout << "\nChoose a number of armies you wish to assign out of " << players[3]->numOfArmies << ": \n";

			cin >> numOfArmiesChosen;

			players[3]->numOfArmies -= numOfArmiesChosen;

			for (Territory* i : players[3]->territories)
			{
				for (Regions* j : i->regions)
				{
					if (j->name == chosenRegion)
					{
						j->numOfArmies += numOfArmiesChosen;
					}
				}
			}
			break;
	}
}

void Player::Attack()
{
	skippedAttackPhase = false;

	switch (playerTurn)
	{
		case 0:
			hasEnoughArmies = false;

			cout << "Choose which of these countries you wish to attack with:\n";

			for (Territory* i : players[0]->territories)
			{
				for (Regions* j : i->regions)
				{
					if (j->numOfArmies > 1)
					{
						cout << j->name << endl;
						hasEnoughArmies = true;
					}
				}
			}

			if (hasEnoughArmies == true)
			{
				cin >> chosenRegion;

				for (Territory* i : players[0]->territories)
				{
					for (Regions* j : i->regions)
					{
						if (j->name == chosenRegion)
						{
							attackingRegion = j;
						}
					}
				}

				enemyRegionsAround = 0;

				for (Regions* i : attackingRegion->adjacentRegions)
				{
					if (i->playerInControl != attackingRegion->playerInControl)  ////// ISSUE IS AROUND HERE BILAL
					{
						enemyRegionsAround += 1;
					}
				}

				if (enemyRegionsAround == 0)
				{
					cout << "\nThere are no enemy countries near your chosen country, skipping to the Fortification phase.\n";
					skippedAttackPhase = true;
					break;
				}

				for (Territory* i : players[0]->territories)
				{
					for (Regions* j : i->regions)
					{
						if (j->name == chosenRegion)
						{
							cout << "Choose an adjacent enemy country to attack:\n";

							for (Regions* k : j->adjacentRegions)
							{
								if (k->playerInControl != 1) 
								{
									cout << k->name << endl;
								}
							}
						}
					}
				}

				cin >> chosenRegion;

				for (Territory* i : players[0]->territories)
				{
					for (Regions* j : i->regions)
					{
						for (Regions* k : j->adjacentRegions)
						{
							if (k->name == chosenRegion)
							{
								defendingRegion = k;
							}
						}
					}
				}

				if (defendingRegion->numOfArmies == 0)
				{
					cout << "\n" << defendingRegion->name << " successfully taken!\n";
					defendingRegion->playerInControl = (playerTurn + 1);

					for (Territory* i : players[0]->territories)
					{
						for (Regions* j : i->regions)
						{
							if (j == defendingRegion)
							{
								TerritoryToRemoveFrom = defendingRegion->returnOwnedTerritory();
								auto element = find(TerritoryToRemoveFrom->regions.begin(), TerritoryToRemoveFrom->regions.end(), j);
								int index = element - TerritoryToRemoveFrom->regions.begin();

								TerritoryToRemoveFrom->regions.erase(TerritoryToRemoveFrom->regions.begin() + index);
							}
						}
					}

					defendingRegion->SetOwnedTerritory(attackingRegion->returnOwnedTerritory());
					attackingRegion->returnOwnedTerritory()->regions.insert(attackingRegion->returnOwnedTerritory()->regions.end(), defendingRegion);

				}
				else
				{
					while (defendingRegion->numOfArmies != 0 || attackingRegion->numOfArmies != 0)
					{
						cout << "\nPlayer " << (playerTurn + 1) << ", pick a number of up to 3 dice to attack!\n";

						cin >> diceNum;

						for (diceNum; diceNum > 0; diceNum--)
						{
							attackerDiceRolls += rand() % 6 + 1;
						}

						cout << "\nPlayer " << defendingRegion->playerInControl << ", pick a number of up to " << attackingRegion->numOfArmies << " dice to attack!\n";

						cin >> diceNum;

						for (diceNum; diceNum > 0; diceNum--)
						{
							defenderDiceRolls += rand() % 6 + 1;
						}

						if (attackerDiceRolls > defenderDiceRolls)
						{
							cout << "\nPlayer " << (playerTurn + 1) << " wins! Player " << defendingRegion->playerInControl << " loses an army.\n";
							defendingRegion->numOfArmies -= 1;
						}
						else
						{
							cout << "\nPlayer " << defendingRegion->playerInControl << " wins! Player " << (playerTurn + 1) << " loses an army.\n";
							attackingRegion->numOfArmies -= 1;
						}
					}
				}

				if (defendingRegion->numOfArmies == 0)
				{
					cout << "\n" << defendingRegion->name << " successfully taken!\n";
					defendingRegion->playerInControl = (playerTurn + 1);

					for (Territory* i : players[0]->territories)
					{
						for (Regions* j : i->regions)
						{
							if (j == defendingRegion)
							{
								TerritoryToRemoveFrom = defendingRegion->returnOwnedTerritory();
								auto element = find(TerritoryToRemoveFrom->regions.begin(), TerritoryToRemoveFrom->regions.end(), j);
								int index = element - TerritoryToRemoveFrom->regions.begin();

								TerritoryToRemoveFrom->regions.erase(TerritoryToRemoveFrom->regions.begin() + index);
							}
						}
					}

					defendingRegion->SetOwnedTerritory(attackingRegion->returnOwnedTerritory());
					attackingRegion->returnOwnedTerritory()->regions.insert(attackingRegion->returnOwnedTerritory()->regions.end(), defendingRegion);
				}
			}
			else
			{
				cout << "You don't have enough armies in any region. Skipping to Fortification phase.\n";
				skippedAttackPhase = true;
			}

			break;
		case 1:
			hasEnoughArmies = false;

			cout << "Choose which of these countries you wish to attack with:\n";

			for (Territory* i : players[1]->territories)
			{
				for (Regions* j : i->regions)
				{
					if (j->numOfArmies > 1)
					{
						cout << j->name << endl;
						hasEnoughArmies = true;
					}
				}
			}

			if (hasEnoughArmies == true)
			{
				cin >> chosenRegion;

				for (Territory* i : players[1]->territories)
				{
					for (Regions* j : i->regions)
					{
						if (j->name == chosenRegion)
						{
							attackingRegion = j;
						}
					}
				}

				enemyRegionsAround = 0;

				for (Regions* i : attackingRegion->adjacentRegions)
				{
					if (i->playerInControl != attackingRegion->playerInControl)  ////// ISSUE IS AROUND HERE BILAL
					{
						enemyRegionsAround += 1;
					}
				}

				if (enemyRegionsAround == 0)
				{
					cout << "\nThere are no enemy countries near your chosen country, skipping to the Fortification phase.\n";
					skippedAttackPhase = true;
					break;
				}

				for (Territory* i : players[1]->territories)
				{
					for (Regions* j : i->regions)
					{
						if (j->name == chosenRegion)
						{
							cout << "Choose an adjacent enemy country to attack:\n";

							for (Regions* k : j->adjacentRegions)
							{
								if (k->playerInControl != 2)
								{
									cout << k->name << endl;
								}
							}
						}
					}
				}

				cin >> chosenRegion;

				for (Territory* i : players[1]->territories)
				{
					for (Regions* j : i->regions)
					{
						for (Regions* k : j->adjacentRegions)
						{
							if (k->name == chosenRegion)
							{
								defendingRegion = k;
							}
						}
					}
				}

				if (defendingRegion->numOfArmies == 0)
				{
					cout << "\n" << defendingRegion->name << " successfully taken!\n";
					defendingRegion->playerInControl = (playerTurn + 1);

					for (Territory* i : players[1]->territories)
					{
						for (Regions* j : i->regions)
						{
							if (j == defendingRegion)
							{
								TerritoryToRemoveFrom = defendingRegion->returnOwnedTerritory();
								auto element = find(TerritoryToRemoveFrom->regions.begin(), TerritoryToRemoveFrom->regions.end(), j);
								int index = element - TerritoryToRemoveFrom->regions.begin();

								TerritoryToRemoveFrom->regions.erase(TerritoryToRemoveFrom->regions.begin() + index);
							}
						}
					}

					defendingRegion->SetOwnedTerritory(attackingRegion->returnOwnedTerritory());
					attackingRegion->returnOwnedTerritory()->regions.insert(attackingRegion->returnOwnedTerritory()->regions.end(), defendingRegion);

				}
				else
				{
					while (defendingRegion->numOfArmies != 0 || attackingRegion->numOfArmies != 0)
					{
						cout << "\nPlayer " << (playerTurn + 1) << ", pick a number of up to 3 dice to attack!\n";

						cin >> diceNum;

						for (diceNum; diceNum > 0; diceNum--)
						{
							attackerDiceRolls += rand() % 6 + 1;
						}

						cout << "\nPlayer " << defendingRegion->playerInControl << ", pick a number of up to " << attackingRegion->numOfArmies << " dice to attack!\n";

						cin >> diceNum;

						for (diceNum; diceNum > 0; diceNum--)
						{
							defenderDiceRolls += rand() % 6 + 1;
						}

						if (attackerDiceRolls > defenderDiceRolls)
						{
							cout << "\nPlayer " << (playerTurn + 1) << " wins! Player " << defendingRegion->playerInControl << " loses an army.\n";
							defendingRegion->numOfArmies -= 1;
						}
						else
						{
							cout << "\nPlayer " << defendingRegion->playerInControl << " wins! Player " << (playerTurn + 1) << " loses an army.\n";
							attackingRegion->numOfArmies -= 1;
						}
					}
				}

				if (defendingRegion->numOfArmies == 0)
				{
					cout << "\n" << defendingRegion->name << " successfully taken!\n";
					defendingRegion->playerInControl = (playerTurn + 1);

					for (Territory* i : players[1]->territories)
					{
						for (Regions* j : i->regions)
						{
							if (j == defendingRegion)
							{
								TerritoryToRemoveFrom = defendingRegion->returnOwnedTerritory();
								auto element = find(TerritoryToRemoveFrom->regions.begin(), TerritoryToRemoveFrom->regions.end(), j);
								int index = element - TerritoryToRemoveFrom->regions.begin();

								TerritoryToRemoveFrom->regions.erase(TerritoryToRemoveFrom->regions.begin() + index);
							}
						}
					}

					defendingRegion->SetOwnedTerritory(attackingRegion->returnOwnedTerritory());
					attackingRegion->returnOwnedTerritory()->regions.insert(attackingRegion->returnOwnedTerritory()->regions.end(), defendingRegion);
				}
			}
			else
			{
				cout << "You don't have enough armies in any region. Skipping to Fortification phase.\n";
				skippedAttackPhase = true;
			}

			break;
		case 2:
			hasEnoughArmies = false;

			cout << "Choose which of these countries you wish to attack with:\n";

			for (Territory* i : players[2]->territories)
			{
				for (Regions* j : i->regions)
				{
					if (j->numOfArmies > 1)
					{
						cout << j->name << endl;
						hasEnoughArmies = true;
					}
				}
			}

			if (hasEnoughArmies == true)
			{
				cin >> chosenRegion;

				for (Territory* i : players[2]->territories)
				{
					for (Regions* j : i->regions)
					{
						if (j->name == chosenRegion)
						{
							attackingRegion = j;
						}
					}
				}

				enemyRegionsAround = 0;

				for (Regions* i : attackingRegion->adjacentRegions)
				{
					cout << "\n" << i->name << endl;

					if (i->playerInControl != attackingRegion->playerInControl)  ////// ISSUE IS AROUND HERE BILAL
					{
						cout << "\n" << attackingRegion->playerInControl << endl;
						enemyRegionsAround += 1;
					}
				}

				if (enemyRegionsAround == 0)
				{
					cout << "\nThere are no enemy countries near your chosen country, skipping to the Fortification phase.\n";
					skippedAttackPhase = true;
					break;
				}

				for (Territory* i : players[2]->territories)
				{
					for (Regions* j : i->regions)
					{
						if (j->name == chosenRegion)
						{
							cout << "Choose an adjacent enemy country to attack:\n";

							for (Regions* k : j->adjacentRegions)
							{
								if (k->playerInControl != 3)
								{
									cout << k->name << endl;
								}
							}
						}
					}
				}

				cin >> chosenRegion;

				for (Territory* i : players[2]->territories)
				{
					for (Regions* j : i->regions)
					{
						for (Regions* k : j->adjacentRegions)
						{
							if (k->name == chosenRegion)
							{
								defendingRegion = k;
							}
						}
					}
				}

				if (defendingRegion->numOfArmies == 0)
				{
					cout << "\n" << defendingRegion->name << " successfully taken!\n";
					defendingRegion->playerInControl = (playerTurn + 1);

					for (Territory* i : players[2]->territories)
					{
						for (Regions* j : i->regions)
						{
							if (j == defendingRegion)
							{
								TerritoryToRemoveFrom = defendingRegion->returnOwnedTerritory();
								auto element = find(TerritoryToRemoveFrom->regions.begin(), TerritoryToRemoveFrom->regions.end(), j);
								int index = element - TerritoryToRemoveFrom->regions.begin();

								TerritoryToRemoveFrom->regions.erase(TerritoryToRemoveFrom->regions.begin() + index);
							}
						}
					}

					defendingRegion->SetOwnedTerritory(attackingRegion->returnOwnedTerritory());
					attackingRegion->returnOwnedTerritory()->regions.insert(attackingRegion->returnOwnedTerritory()->regions.end(), defendingRegion);

				}
				else
				{
					while (defendingRegion->numOfArmies != 0 || attackingRegion->numOfArmies != 0)
					{
						cout << "\nPlayer " << (playerTurn + 1) << ", pick a number of up to 3 dice to attack!\n";

						cin >> diceNum;

						for (diceNum; diceNum > 0; diceNum--)
						{
							attackerDiceRolls += rand() % 6 + 1;
						}

						cout << "\nPlayer " << defendingRegion->playerInControl << ", pick a number of up to " << attackingRegion->numOfArmies << " dice to attack!\n";

						cin >> diceNum;

						for (diceNum; diceNum > 0; diceNum--)
						{
							defenderDiceRolls += rand() % 6 + 1;
						}

						if (attackerDiceRolls > defenderDiceRolls)
						{
							cout << "\nPlayer " << (playerTurn + 1) << " wins! Player " << defendingRegion->playerInControl << " loses an army.\n";
							defendingRegion->numOfArmies -= 1;
						}
						else
						{
							cout << "\nPlayer " << defendingRegion->playerInControl << " wins! Player " << (playerTurn + 1) << " loses an army.\n";
							attackingRegion->numOfArmies -= 1;
						}
					}
				}

				if (defendingRegion->numOfArmies == 0)
				{
					cout << "\n" << defendingRegion->name << " successfully taken!\n";
					defendingRegion->playerInControl = (playerTurn + 1);

					for (Territory* i : players[2]->territories)
					{
						for (Regions* j : i->regions)
						{
							if (j == defendingRegion)
							{
								TerritoryToRemoveFrom = defendingRegion->returnOwnedTerritory();
								auto element = find(TerritoryToRemoveFrom->regions.begin(), TerritoryToRemoveFrom->regions.end(), j);
								int index = element - TerritoryToRemoveFrom->regions.begin();

								TerritoryToRemoveFrom->regions.erase(TerritoryToRemoveFrom->regions.begin() + index);
							}
						}
					}

					defendingRegion->SetOwnedTerritory(attackingRegion->returnOwnedTerritory());
					attackingRegion->returnOwnedTerritory()->regions.insert(attackingRegion->returnOwnedTerritory()->regions.end(), defendingRegion);
				}
			}
			else
			{
				cout << "You don't have enough armies in any region. Skipping to Fortification phase.\n";
				skippedAttackPhase = true;
			}

			break;
		case 3:
			hasEnoughArmies = false;

			cout << "Choose which of these countries you wish to attack with:\n";

			for (Territory* i : players[3]->territories)
			{
				for (Regions* j : i->regions)
				{
					if (j->numOfArmies > 1)
					{
						cout << j->name << endl;
						hasEnoughArmies = true;
					}
				}
			}

			if (hasEnoughArmies == true)
			{
				cin >> chosenRegion;

				for (Territory* i : players[3]->territories)
				{
					for (Regions* j : i->regions)
					{
						if (j->name == chosenRegion)
						{
							attackingRegion = j;
						}
					}
				}

				enemyRegionsAround = 0;

				for (Regions* i : attackingRegion->adjacentRegions)
				{
					if (i->playerInControl != attackingRegion->playerInControl)  ////// ISSUE IS AROUND HERE BILAL
					{
						enemyRegionsAround += 1;
					}
				}

				if (enemyRegionsAround == 0)
				{
					cout << "\nThere are no enemy countries near your chosen country, skipping to the Fortification phase.\n";
					skippedAttackPhase = true;
					break;
				}

				for (Territory* i : players[3]->territories)
				{
					for (Regions* j : i->regions)
					{
						if (j->name == chosenRegion)
						{
							cout << "Choose an adjacent enemy country to attack:\n";

							for (Regions* k : j->adjacentRegions)
							{
								if (k->playerInControl != 4)
								{
									cout << k->name << endl;
								}
							}
						}
					}
				}

				cin >> chosenRegion;

				for (Territory* i : players[3]->territories)
				{
					for (Regions* j : i->regions)
					{
						for (Regions* k : j->adjacentRegions)
						{
							if (k->name == chosenRegion)
							{
								defendingRegion = k;
							}
						}
					}
				}

				if (defendingRegion->numOfArmies == 0)
				{
					cout << "\n" << defendingRegion->name << " successfully taken!\n";
					defendingRegion->playerInControl = (playerTurn + 1);

					for (Territory* i : players[3]->territories)
					{
						for (Regions* j : i->regions)
						{
							if (j == defendingRegion)
							{
								TerritoryToRemoveFrom = defendingRegion->returnOwnedTerritory();
								auto element = find(TerritoryToRemoveFrom->regions.begin(), TerritoryToRemoveFrom->regions.end(), j);
								int index = element - TerritoryToRemoveFrom->regions.begin();

								TerritoryToRemoveFrom->regions.erase(TerritoryToRemoveFrom->regions.begin() + index);
							}
						}
					}

					defendingRegion->SetOwnedTerritory(attackingRegion->returnOwnedTerritory());
					attackingRegion->returnOwnedTerritory()->regions.insert(attackingRegion->returnOwnedTerritory()->regions.end(), defendingRegion);

				}
				else
				{
					while (defendingRegion->numOfArmies != 0 || attackingRegion->numOfArmies != 0)
					{
						cout << "\nPlayer " << (playerTurn + 1) << ", pick a number of up to 3 dice to attack!\n";

						cin >> diceNum;

						for (diceNum; diceNum > 0; diceNum--)
						{
							attackerDiceRolls += rand() % 6 + 1;
						}

						cout << "\nPlayer " << defendingRegion->playerInControl << ", pick a number of up to " << attackingRegion->numOfArmies << " dice to attack!\n";

						cin >> diceNum;

						for (diceNum; diceNum > 0; diceNum--)
						{
							defenderDiceRolls += rand() % 6 + 1;
						}

						if (attackerDiceRolls > defenderDiceRolls)
						{
							cout << "\nPlayer " << (playerTurn + 1) << " wins! Player " << defendingRegion->playerInControl << " loses an army.\n";
							defendingRegion->numOfArmies -= 1;
						}
						else
						{
							cout << "\nPlayer " << defendingRegion->playerInControl << " wins! Player " << (playerTurn + 1) << " loses an army.\n";
							attackingRegion->numOfArmies -= 1;
						}
					}
				}

				if (defendingRegion->numOfArmies == 0)
				{
					cout << "\n" << defendingRegion->name << " successfully taken!\n";
					defendingRegion->playerInControl = (playerTurn + 1);

					for (Territory* i : players[3]->territories)
					{
						for (Regions* j : i->regions)
						{
							if (j == defendingRegion)
							{
								TerritoryToRemoveFrom = defendingRegion->returnOwnedTerritory();
								auto element = find(TerritoryToRemoveFrom->regions.begin(), TerritoryToRemoveFrom->regions.end(), j);
								int index = element - TerritoryToRemoveFrom->regions.begin();

								TerritoryToRemoveFrom->regions.erase(TerritoryToRemoveFrom->regions.begin() + index);
							}
						}
					}

					defendingRegion->SetOwnedTerritory(attackingRegion->returnOwnedTerritory());
					attackingRegion->returnOwnedTerritory()->regions.insert(attackingRegion->returnOwnedTerritory()->regions.end(), defendingRegion);
				}
			}
			else
			{
				cout << "You don't have enough armies in any region. Skipping to Fortification phase.\n";
				skippedAttackPhase = true;
			}

			break;
	}
}

void Player::Fortificate()
{
	cout << "\nfortify";
}