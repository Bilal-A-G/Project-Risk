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

Mesh northAmerica;
Camera camera;

float height = 500;
float width = 500;

void CreateBoard()
{
	mainWindow = new Window(width, height, "Window");
	mainWindow->SetClearColour(0.0f, 0.0f, 0.0f, 1.0f);

	std::vector<char> fragSource = FileReader::ReadFile("Fragment");
	std::vector<char> vertSource = FileReader::ReadFile("Vertex");

	shader.Compile(vertSource, ShaderType::VERTEX);
	shader.Compile(fragSource, ShaderType::FRAGMENT);

	shader.Link();


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

	northAmerica.Create(bufferData, indices, "map");
}

void Start()
{
	//TerritorySetup();
	
	/* testing territory setup
	
	for (Territory* i : territories)
	{
		for (Regions* j : i->regions)
		{
			cout << j->name << '\n';
		}
	}
	
	*/

	//cout << "Please write a number of players between 2 to 4: \n";
	//cin >> playerCount;

	//if (playerCount < 2)
	//{
	//	playerCount = 2;
	//}
	//else if (playerCount > 4)
	//{
	//	playerCount = 4;
	//}

	//for (int i = 1; i <= playerCount; ++i)
	//{
	//	players.push_back(new Player());
	//}

	//for (int i = 1; i <= players.size(); ++i)
	//{
	//	int territoryNum = rand() % 6 + 1;

	//	switch (territoryNum)
	//	{
	//		case 1:
	//			if (onePicked == false)
	//			{
	//				for (Territory* j : territories)
	//				{
	//					if (j->name == "NorthAmerica")
	//					{
	//						j->playerInControl = i;
	//						players[i - 1]->territories.insert(players[i - 1]->territories.end(), {NorthAmerica});
	//					}
	//				}

	//				onePicked = true; // makes sure nortAmerica doesn't get assigned to more than one person
	//			}
	//			else
	//			{
	//				i--; // if the number was already picked, reset i so that it doesn't skip over the player and assigns a new number
	//				break;
	//			}
	//			break;
	//		case 2:
	//			if (twoPicked == false)
	//			{
	//				for (Territory* j : territories)
	//				{
	//					if (j->name == "SouthAmerica")
	//					{
	//						j->playerInControl = i;
	//						players[i - 1]->territories.insert(players[i - 1]->territories.end(), {SouthAmerica});
	//					}
	//				}
	//				twoPicked = true; // makes sure southAmerica doesn't get assigned to more than one person
	//			}
	//			else
	//			{
	//				i--; // if the number was already picked, reset i so that it doesn't skip over the player and assigns a new number
	//				break;
	//			}
	//			break;
	//		case 3:
	//			if (threePicked == false)
	//			{
	//				for (Territory* j : territories)
	//				{
	//					if (j->name == "Europe")
	//					{
	//						j->playerInControl = i;
	//						players[i - 1]->territories.insert(players[i - 1]->territories.end(), {Europe});
	//					}
	//				}
	//				threePicked = true; // makes sure eurasia doesn't get assigned to more than one person
	//			}
	//			else
	//			{
	//				i--; // if the number was already picked, reset i so that it doesn't skip over the player and assigns a new number
	//				break;
	//			}
	//			break;
	//		case 4:
	//			if (fourPicked == false)
	//			{
	//				for (Territory* j : territories)
	//				{
	//					if (j->name == "Asia")
	//					{
	//						j->playerInControl = i;
	//						players[i - 1]->territories.insert(players[i - 1]->territories.end(), {Asia});
	//					}
	//				}
	//				fourPicked = true; // makes sure africa doesn't get assigned to more than one person
	//			}
	//			else
	//			{
	//				i--; // if the number was already picked, reset i so that it doesn't skip over the player and assigns a new number
	//				break;
	//			}
	//			break;
	//		case 5:
	//			if (fivePicked == false)
	//			{
	//				for (Territory* j : territories)
	//				{
	//					if (j->name == "Oceania")
	//					{
	//						j->playerInControl = i;
	//						players[i - 1]->territories.insert(players[i - 1]->territories.end(), {Oceania});
	//					}
	//				}
	//				fivePicked = true; // makes sure africa doesn't get assigned to more than one person
	//			}
	//			else
	//			{
	//				i--; // if the number was already picked, reset i so that it doesn't skip over the player and assigns a new number
	//				break;
	//			}
	//			break;
	//		case 6:
	//			if (sixPicked == false)
	//			{
	//				for (Territory* j : territories)
	//				{
	//					if (j->name == "Africa")
	//					{
	//						j->playerInControl = i;
	//						players[i - 1]->territories.insert(players[i - 1]->territories.end(), {Africa});
	//					}
	//				}
	//				sixPicked = true; // makes sure africa doesn't get assigned to more than one person
	//			}
	//			else
	//			{
	//				i--; // if the number was already picked, reset i so that it doesn't skip over the player and assigns a new number
	//				break;
	//			}
	//			break;
	//	}
	//}

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

	glm::mat4 perspective = glm::perspective(90.0f, (float)mainWindow->width / (float)mainWindow->height, 0.01f, 100.0f);
	perspective = glm::rotate(perspective, -6.86f, glm::vec3(1.0f, 0.0f, 0.0f));
	std::cout << mainWindow->width << "\n";
	northAmerica.SetProjection(perspective);
	northAmerica.Draw(shader);

	//camera.Update(view, *mainWindow);

	//switch (playerTurn)
	//{
	//	case 0: // player 1 turn
	//		cout << "\nPlayer 1's Turn.\n";
	//		players[0]->Reinforcement();
	//		players[0]->Attack();
	//		players[0]->Fortificate();

	//		playerTurn = 1; // set to player 2 turn
	//		
	//		break;
	//	case 1: // player 2 turn
	//		cout << "\nPlayer 2's Turn.\n";
	//		players[1]->Reinforcement();
	//		players[1]->Attack();
	//		players[1]->Fortificate();

	//		if (playerCount > 2)
	//		{
	//			playerTurn = 2; // set to player 3 turn
	//		}
	//		else
	//		{
	//			playerTurn = 0; // set to player 1 turn if there is no player 3
	//		}
	//		
	//		break;
	//	case 2: // player 3 turn
	//		cout << "\nPlayer 3's Turn.\n";
	//		players[2]->Reinforcement();
	//		players[2]->Attack();
	//		players[2]->Fortificate();

	//		if (playerCount > 3)
	//		{
	//			playerTurn = 3; // set to player 4 turn
	//		}
	//		else
	//		{
	//			playerTurn = 0; // set to player 1 turn if there is no player 4
	//		}

	//		break;
	//	case 3: // player 4 turn
	//		cout << "\nPlayer 4's Turn.\n";
	//		players[3]->Reinforcement();
	//		players[3]->Attack();
	//		players[3]->Fortificate();

	//		playerTurn = 0; // set to player 1 turn
	//		break;
	//}
}

//void TerritorySetup()
//{
//	// North America
//	NorthAmerica->name = "NorthAmerica";
//	Regions* Alaska = new Regions();
//	Alaska->name = "Alaska";
//	Regions* NorthwestTerritory = new Regions();
//	NorthwestTerritory->name = "NorthwestTerritory";
//	Regions* Greenland = new Regions();
//	Greenland->name = "Greenland";
//	Regions* Alberta = new Regions();
//	Alberta->name = "Alberta";
//	Regions* Ontario = new Regions();
//	Ontario->name = "Ontario";
//	Regions* Quebec = new Regions();
//	Quebec->name = "Quebec";
//	Regions* WesternUnitedStates = new Regions();
//	WesternUnitedStates->name = "WesternUnitedStates";
//	Regions* EasternUnitedStates = new Regions();
//	EasternUnitedStates->name = "EasternUnitedStates";
//	Regions* CentralAmerica = new Regions();
//	CentralAmerica->name = "CentralAmerica";
//	Regions* EasternCanada = new Regions();
//	EasternCanada->name = "EasternCanada";
//
//	NorthAmerica->regions.insert(NorthAmerica->regions.end(), 
//		{Alaska, NorthwestTerritory, Greenland, Alberta, Ontario, Quebec, WesternUnitedStates, EasternUnitedStates, CentralAmerica, EasternCanada});
//
//	// South America
//	SouthAmerica->name = "SouthAmerica";
//	Regions* Venezuela = new Regions();
//	Venezuela->name = "Venezuela";
//	Regions* Peru = new Regions();
//	Peru->name = "Peru";
//	Regions* Brazil = new Regions();
//	Brazil->name = "Brazil";
//	Regions* Argentina = new Regions();
//	Argentina->name = "Argentina";
//
//	SouthAmerica->regions.insert(SouthAmerica->regions.end(),
//		{Venezuela, Peru, Brazil, Argentina});
//
//	// Africa
//	Africa->name = "Africa";
//	Regions* NorthAfrica = new Regions();
//	NorthAfrica->name = "NorthAfrica";
//	Regions* Egypt = new Regions();
//	Egypt->name = "Egypt";
//	Regions* EastAfrica = new Regions();
//	EastAfrica->name = "EastAfrica";
//	Regions* SouthAfrica = new Regions();
//	SouthAfrica->name = "SouthAfrica";
//	Regions* Madagascar = new Regions();
//	Madagascar->name = "Madagascar";
//	Regions* CentralAfrica = new Regions();
//	CentralAfrica->name = "CentralAfrica";
//
//	Africa->regions.insert(Africa->regions.end(),
//		{NorthAfrica, Egypt, EastAfrica, CentralAfrica, SouthAfrica, Madagascar});
//
//	// Europe
//	Europe->name = "Europe";
//	Regions* Iceland = new Regions();
//	Iceland->name = "Iceland";
//	Regions* Scandinavia = new Regions();
//	Scandinavia->name = "Scandinavia";
//	Regions* GreatBritain = new Regions();
//	GreatBritain->name = "GreatBritain";
//	Regions* NorthernEurope = new Regions();
//	NorthernEurope->name = "NorthernEurope";
//	Regions* SouthernEurope = new Regions();
//	SouthernEurope->name = "SouthernEurope";
//	Regions* WesternEurope = new Regions();
//	WesternEurope->name = "WesternEurope";
//	Regions* Russia = new Regions();
//	Russia->name = "Russia";
//
//	Europe->regions.insert(Europe->regions.end(),
//		{Iceland, Scandinavia, Russia, GreatBritain, NorthernEurope, SouthernEurope, WesternEurope});
//
//	// Oceania
//	Oceania->name = "Oceania";
//	Regions* Indonesia = new Regions();
//	Indonesia->name = "Indonesia";
//	Regions* NewGuinea = new Regions();
//	NewGuinea->name = "NewGuinea";
//	Regions* WesternAustralia = new Regions();
//	WesternAustralia->name = "WesternAustralia";
//	Regions* EasternAustralia = new Regions();
//	EasternAustralia->name = "EasternAustralia";
//
//	Oceania->regions.insert(Oceania->regions.end(),
//		{Indonesia, NewGuinea, WesternAustralia, EasternAustralia});
//
//	// Asia
//	Asia->name = "Asia";
//	Regions* Siam = new Regions();
//	Siam->name = "Siam";
//	Regions* India = new Regions();
//	India->name = "India";
//	Regions* China = new Regions();
//	China->name = "China";
//	Regions* Mongolia = new Regions();
//	Mongolia->name = "Mongolia";
//	Regions* Japan = new Regions();
//	Japan->name = "Japan";
//	Regions* Irkutsk = new Regions();
//	Irkutsk->name = "Irkutsk";
//	Regions* Yakutsk = new Regions();
//	Yakutsk->name = "Yakutsk";
//	Regions* Kamchatka = new Regions();
//	Kamchatka->name = "Kamchatka";
//	Regions* Siberia = new Regions();
//	Siberia->name = "Siberia";
//	Regions* Afghanistan = new Regions();
//	Afghanistan->name = "Afghanistan";
//	Regions* Ural = new Regions();
//	Ural->name = "Ural";
//	Regions* MiddleEast = new Regions();
//	MiddleEast->name = "MiddleEast";
//	Regions* SoutheastAsia = new Regions();
//	SoutheastAsia->name = "SoutheastAsia";
//
//	Asia->regions.insert(Asia->regions.end(),
//		{Siam, India, China, Mongolia, Japan, Irkutsk, Yakutsk, Kamchatka, Siberia, Afghanistan, Ural, MiddleEast, SoutheastAsia});
//
//	// Adding Territories to Vector
//
//	territories.insert(territories.end(), {NorthAmerica, SouthAmerica, Africa, Europe, Asia, Oceania});
//
//	// North America Adjacents
//
//	Greenland->adjacentRegions.insert(Greenland->adjacentRegions.end(),
//		{ NorthwestTerritory, Ontario, EasternCanada, Iceland});
//
//	Alaska->adjacentRegions.insert(Alaska->adjacentRegions.end(),
//		{NorthwestTerritory, Alberta, Kamchatka});
//
//	NorthwestTerritory->adjacentRegions.insert(NorthwestTerritory->adjacentRegions.end(),
//		{Alaska, Alberta, Ontario, Greenland});
//
//	Alberta->adjacentRegions.insert(Alberta->adjacentRegions.end(),
//		{Alaska, NorthwestTerritory, Ontario, WesternUnitedStates});
//
//	Ontario->adjacentRegions.insert(Ontario->adjacentRegions.end(),
//		{NorthwestTerritory, Alberta, EasternCanada, WesternUnitedStates, EasternUnitedStates, Greenland});
//
//	EasternCanada->adjacentRegions.insert(EasternCanada->adjacentRegions.end(),
//		{Greenland, Ontario, EasternUnitedStates});
//
//	WesternUnitedStates->adjacentRegions.insert(WesternUnitedStates->adjacentRegions.end(),
//		{Alberta, Ontario, EasternUnitedStates, CentralAmerica});
//
//	EasternUnitedStates->adjacentRegions.insert(EasternUnitedStates->adjacentRegions.end(),
//		{WesternUnitedStates, CentralAmerica, Ontario, EasternCanada});
//
//	CentralAmerica->adjacentRegions.insert(CentralAmerica->adjacentRegions.end(),
//		{WesternUnitedStates, EasternUnitedStates, Venezuela});
//
//	// South America Adjacents
//
//	Venezuela->adjacentRegions.insert(Venezuela->adjacentRegions.end(),
//		{CentralAmerica, Peru, Brazil});
//
//	Peru->adjacentRegions.insert(Peru->adjacentRegions.end(),
//		{Venezuela, Brazil, Argentina});
//
//	Brazil->adjacentRegions.insert(Brazil->adjacentRegions.end(),
//		{Venezuela, Peru, Argentina, NorthAfrica});
//
//	Argentina->adjacentRegions.insert(Argentina->adjacentRegions.end(),
//		{Peru, Brazil});
//
//	// Europe Adjacents
//
//	Iceland->adjacentRegions.insert(Iceland->adjacentRegions.end(),
//		{Greenland, GreatBritain, Scandinavia});
//
//	GreatBritain->adjacentRegions.insert(GreatBritain->adjacentRegions.end(),
//		{Iceland, Scandinavia, NorthernEurope, WesternEurope});
//
//	WesternEurope->adjacentRegions.insert(WesternEurope->adjacentRegions.end(),
//		{GreatBritain, NorthernEurope, SouthernEurope, NorthAfrica});
//
//	Scandinavia->adjacentRegions.insert(Scandinavia->adjacentRegions.end(),
//		{Iceland, GreatBritain, NorthernEurope, Russia});
//
//	NorthernEurope->adjacentRegions.insert(NorthernEurope->adjacentRegions.end(),
//		{GreatBritain, Scandinavia, WesternEurope, SouthernEurope, Russia});
//
//	SouthernEurope->adjacentRegions.insert(SouthernEurope->adjacentRegions.end(),
//		{WesternEurope, NorthernEurope, Russia, MiddleEast, NorthAfrica, Egypt});
//
//	Russia->adjacentRegions.insert(Russia->adjacentRegions.end(),
//		{Scandinavia, NorthernEurope, SouthernEurope, MiddleEast, Ural, Afghanistan});
//
//	// Africa Adjacents
//
//	NorthAfrica->adjacentRegions.insert(NorthAfrica->adjacentRegions.end(),
//		{Brazil, WesternEurope, SouthernEurope, Egypt, EastAfrica, CentralAfrica});
//
//	Egypt->adjacentRegions.insert(Egypt->adjacentRegions.end(),
//		{NorthAfrica, SouthernEurope, MiddleEast, EastAfrica});
//
//	EastAfrica->adjacentRegions.insert(EastAfrica->adjacentRegions.end(),
//		{NorthAfrica, Egypt, CentralAfrica, SouthAfrica, Madagascar, MiddleEast});
//
//	CentralAfrica->adjacentRegions.insert(CentralAfrica->adjacentRegions.end(),
//		{NorthAfrica, EastAfrica, SouthAfrica});
//
//	SouthAfrica->adjacentRegions.insert(SouthAfrica->adjacentRegions.end(),
//		{CentralAfrica, EastAfrica, Madagascar});
//
//	Madagascar->adjacentRegions.insert(Madagascar->adjacentRegions.end(),
//		{SouthAfrica, EastAfrica});
//
//	// Asia Adjacents
//
//	MiddleEast->adjacentRegions.insert(MiddleEast->adjacentRegions.end(),
//		{SouthernEurope, Russia, Egypt, EastAfrica, Afghanistan, India});
//
//	Afghanistan->adjacentRegions.insert(Afghanistan->adjacentRegions.end(),
//		{Russia, MiddleEast, Ural, China, India});
//
//	Ural->adjacentRegions.insert(Ural->adjacentRegions.end(),
//		{Siberia, Russia, Afghanistan, China});
//
//	Siberia->adjacentRegions.insert(Siberia->adjacentRegions.end(),
//		{Ural, Yakutsk, Irkutsk, China, Mongolia});
//
//	Yakutsk->adjacentRegions.insert(Yakutsk->adjacentRegions.end(),
//		{Siberia, Kamchatka, Irkutsk});
//
//	Kamchatka->adjacentRegions.insert(Kamchatka->adjacentRegions.end(),
//		{Yakutsk, Irkutsk, Mongolia, Japan, Alaska});
//
//	Irkutsk->adjacentRegions.insert(Irkutsk->adjacentRegions.end(),
//		{Yakutsk, Siberia, Mongolia, Kamchatka});
//
//	Mongolia->adjacentRegions.insert(Mongolia->adjacentRegions.end(),
//		{Siberia, Irkutsk, Kamchatka, Japan, China});
//
//	Japan->adjacentRegions.insert(Japan->adjacentRegions.end(),
//		{Kamchatka, Mongolia});
//
//	China->adjacentRegions.insert(China->adjacentRegions.end(),
//		{SoutheastAsia, India, Afghanistan, Ural, Siberia, Mongolia});
//
//	India->adjacentRegions.insert(India->adjacentRegions.end(),
//		{MiddleEast, Afghanistan, China, SoutheastAsia});
//
//	SoutheastAsia->adjacentRegions.insert(SoutheastAsia->adjacentRegions.end(),
//		{India, China, Indonesia});
//
//	// Oceania Adjacents
//
//	Indonesia->adjacentRegions.insert(Indonesia->adjacentRegions.end(),
//		{SoutheastAsia, NewGuinea, WesternAustralia});
//
//	NewGuinea->adjacentRegions.insert(NewGuinea->adjacentRegions.end(),
//		{Indonesia, EasternAustralia});
//
//	WesternAustralia->adjacentRegions.insert(WesternAustralia->adjacentRegions.end(),
//		{Indonesia, EasternAustralia});
//
//	EasternAustralia->adjacentRegions.insert(EasternAustralia->adjacentRegions.end(),
//		{WesternAustralia, NewGuinea});
//}