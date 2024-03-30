#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Core/main.cpp"
#include "iostream"
#include "glm/glm.hpp"
#include "Territories/Territories.h"
#include "Window/Window.h"
#include "IO/FileReader.h"
#include "Player/Player.h"
#include "time.h"

using namespace std;

Window* mainWindow;
Shader shader;
Mesh map;

float height = 600;
float width = 1000;

int playerCount = 0;
int playerTurn = 0;

std::vector<Territory*> territories;
vector<Player> players;

void SetUpTerritories(std::vector<float> bufferData, std::vector<int> indices) 
{
	glm::mat4 territoryEmptyScale = glm::scale(glm::mat4(1), glm::vec3(0.015f, 0.03f, 0.03f));

	//North America Territories
	Mesh alaska = Mesh();
	alaska.Create(bufferData, indices, "BlankTile");
	alaska.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-60.0f, 23.0f, 0.0f)));
	Territory* alaska_Terr = new Territory("Alaska", alaska);
	territories.push_back(alaska_Terr);

	Mesh nwTerritories = Mesh();
	nwTerritories.Create(bufferData, indices, "BlankTile");
	nwTerritories.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-50.0f, 23.0f, 0.0f)));
	Territory* nwTerritories_Terr = new Territory("Northwest Territories", nwTerritories);
	territories.push_back(nwTerritories_Terr);

	Mesh alberta = Mesh();
	alberta.Create(bufferData, indices, "BlankTile");
	alberta.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-50.0f, 17.0f, 0.0f)));
	Territory* alberta_Terr = new Territory("Alberta", alberta);
	territories.push_back(alberta_Terr);

	Mesh ontario = Mesh();
	ontario.Create(bufferData, indices, "BlankTile");
	ontario.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-43.0f, 17.0f, 0.0f)));
	Territory* ontario_Terr = new Territory("Ontario", ontario);
	territories.push_back(ontario_Terr);

	Mesh quebec = Mesh();
	quebec.Create(bufferData, indices, "BlankTile");
	quebec.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-35.0f, 15.0f, 0.0f)));
	Territory* quebec_Terr = new Territory("Quebec", quebec);
	territories.push_back(quebec_Terr);

	Mesh westernUS = Mesh();
	westernUS.Create(bufferData, indices, "BlankTile");
	westernUS.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-50.0f, 10.0f, 0.0f)));
	Territory* westernUS_Terr = new Territory("Western United States", westernUS);
	territories.push_back(westernUS_Terr);

	Mesh easternUS = Mesh();
	easternUS.Create(bufferData, indices, "BlankTile");
	easternUS.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-40.0f, 8.0f, 0.0f)));
	Territory* easternUS_Terr = new Territory("Eastern United States", easternUS);
	territories.push_back(easternUS_Terr);

	Mesh centralAmerica = Mesh();
	centralAmerica.Create(bufferData, indices, "BlankTile");
	centralAmerica.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-47.0f, 1.0f, 0.0f)));
	Territory* centralAmerica_Terr = new Territory("Central America", centralAmerica);
	territories.push_back(centralAmerica_Terr);

	Mesh greenland = Mesh();
	greenland.Create(bufferData, indices, "BlankTile");
	greenland.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-28.0f, 25.0f, 0.0f)));
	Territory* greenland_Terr = new Territory("Greenland", greenland);
	territories.push_back(greenland_Terr);

	//South America Territories
	Mesh venezuela = Mesh();
	venezuela.Create(bufferData, indices, "BlankTile");
	venezuela.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-40.0f, -5.0f, 0.0f)));
	Territory* venezuela_Terr = new Territory("Venezuela", venezuela);
	territories.push_back(venezuela_Terr);

	Mesh peru = Mesh();
	peru.Create(bufferData, indices, "BlankTile");
	peru.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-40.0f, -13.0f, 0.0f)));
	Territory* peru_Terr = new Territory("Peru", peru);
	territories.push_back(peru_Terr);

	Mesh brazil = Mesh();
	brazil.Create(bufferData, indices, "BlankTile");
	brazil.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-30.0f, -13.0f, 0.0f)));
	Territory* brazil_Terr = new Territory("Brazil", brazil);
	territories.push_back(brazil_Terr);

	Mesh argentina = Mesh();
	argentina.Create(bufferData, indices, "BlankTile");
	argentina.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-37.0f, -20.0f, 0.0f)));
	Territory* argentina_Terr = new Territory("Argentina", argentina);
	territories.push_back(argentina_Terr);

	//Europe Territories
	Mesh uk = Mesh();
	uk.Create(bufferData, indices, "BlankTile");
	uk.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-18.0f, 11.0f, 0.0f)));
	Territory* uk_Terr = new Territory("United Kingdom", uk);
	territories.push_back(uk_Terr);

	Mesh westernEU = Mesh();
	westernEU.Create(bufferData, indices, "BlankTile");
	westernEU.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-18.0f, 2.0f, 0.0f)));
	Territory* westernEU_Terr = new Territory("Western Europe", westernEU);
	territories.push_back(westernEU_Terr);

	Mesh southernEU = Mesh();
	southernEU.Create(bufferData, indices, "BlankTile");
	southernEU.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-8.0f, 5.0f, 0.0f)));
	Territory* southernEU_Terr = new Territory("Southern Europe", southernEU);
	territories.push_back(southernEU_Terr);

	Mesh northernEU = Mesh();
	northernEU.Create(bufferData, indices, "BlankTile");
	northernEU.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-8.0f, 11.0f, 0.0f)));
	Territory* northernEU_Terr = new Territory("Northern Europe", northernEU);
	territories.push_back(northernEU_Terr);

	Mesh ukraine = Mesh();
	ukraine.Create(bufferData, indices, "BlankTile");
	ukraine.SetModel(glm::translate(territoryEmptyScale, glm::vec3(2.0f, 15.0f, 0.0f)));
	Territory* ukraine_Terr = new Territory("Ukraine", ukraine);
	territories.push_back(ukraine_Terr);

	Mesh scandinavia = Mesh();
	scandinavia.Create(bufferData, indices, "BlankTile");
	scandinavia.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-8.0f, 20.0f, 0.0f)));
	Territory* scandinavia_Terr = new Territory("Scandinavia", scandinavia);
	territories.push_back(scandinavia_Terr);

	Mesh iceland = Mesh();
	iceland.Create(bufferData, indices, "BlankTile");
	iceland.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-17.0f, 20.0f, 0.0f)));
	Territory* iceland_Terr = new Territory("Iceland", iceland);
	territories.push_back(iceland_Terr);

	//Africa Territories
	Mesh northAfrica = Mesh();
	northAfrica.Create(bufferData, indices, "BlankTile");
	northAfrica.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-10.0f, -8.0f, 0.0f)));
	Territory* northAfrica_Terr = new Territory("North Africa", northAfrica);
	territories.push_back(northAfrica_Terr);

	Mesh egypt = Mesh();
	egypt.Create(bufferData, indices, "BlankTile");
	egypt.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-2.0f, -6.0f, 0.0f)));
	Territory* egypt_Terr = new Territory("Egypt", egypt);
	territories.push_back(egypt_Terr);

	Mesh eastAfrica = Mesh();
	eastAfrica.Create(bufferData, indices, "BlankTile");
	eastAfrica.SetModel(glm::translate(territoryEmptyScale, glm::vec3(3.0f, -15.0f, 0.0f)));
	Territory* eastAfrica_Terr = new Territory("East Africa", eastAfrica);
	territories.push_back(eastAfrica_Terr);

	Mesh congo = Mesh();
	congo.Create(bufferData, indices, "BlankTile");
	congo.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-3.0f, -18.0f, 0.0f)));
	Territory* congo_Terr = new Territory("Congo", congo);
	territories.push_back(congo_Terr);

	Mesh southAfrica = Mesh();
	southAfrica.Create(bufferData, indices, "BlankTile");
	southAfrica.SetModel(glm::translate(territoryEmptyScale, glm::vec3(-3.0f, -26.0f, 0.0f)));
	Territory* southAfrica_Terr = new Territory("South Africa", southAfrica);
	territories.push_back(southAfrica_Terr);

	Mesh madagascar = Mesh();
	madagascar.Create(bufferData, indices, "BlankTile");
	madagascar.SetModel(glm::translate(territoryEmptyScale, glm::vec3(8.0f, -26.0f, 0.0f)));
	Territory* madagascar_Terr = new Territory("Madagascar", madagascar);
	territories.push_back(madagascar_Terr);

	//Asia Territories
	Mesh middleEast = Mesh();
	middleEast.Create(bufferData, indices, "BlankTile");
	middleEast.SetModel(glm::translate(territoryEmptyScale, glm::vec3(4.0f, 0.0f, 0.0f)));
	Territory* middleEast_Terr = new Territory("Middle East", middleEast);
	territories.push_back(middleEast_Terr);

	Mesh india = Mesh();
	india.Create(bufferData, indices, "BlankTile");
	india.SetModel(glm::translate(territoryEmptyScale, glm::vec3(18.0f, -2.0f, 0.0f)));
	Territory* india_Terr = new Territory("India", india);
	territories.push_back(india_Terr);

	Mesh siam = Mesh();
	siam.Create(bufferData, indices, "BlankTile");
	siam.SetModel(glm::translate(territoryEmptyScale, glm::vec3(30.0f, -5.0f, 0.0f)));
	Territory* siam_Terr = new Territory("Siam", siam);
	territories.push_back(siam_Terr);

	Mesh china = Mesh();
	china.Create(bufferData, indices, "BlankTile");
	china.SetModel(glm::translate(territoryEmptyScale, glm::vec3(30.0f, 2.0f, 0.0f)));
	Territory* china_Terr = new Territory("China", china);
	territories.push_back(china_Terr);

	Mesh mongolia = Mesh();
	mongolia.Create(bufferData, indices, "BlankTile");
	mongolia.SetModel(glm::translate(territoryEmptyScale, glm::vec3(30.0f, 10.0f, 0.0f)));
	Territory* mongolia_Terr = new Territory("Mongolia", mongolia);
	territories.push_back(mongolia_Terr);

	Mesh irkutsk = Mesh();
	irkutsk.Create(bufferData, indices, "BlankTile");
	irkutsk.SetModel(glm::translate(territoryEmptyScale, glm::vec3(30.0f, 18.0f, 0.0f)));
	Territory* irkutsk_Terr = new Territory("Irkutsk", irkutsk);
	territories.push_back(irkutsk_Terr);

	Mesh yakutsk = Mesh();
	yakutsk.Create(bufferData, indices, "BlankTile");
	yakutsk.SetModel(glm::translate(territoryEmptyScale, glm::vec3(30.0f, 25.0f, 0.0f)));
	Territory* yakutsk_Terr = new Territory("Yakutsk", yakutsk);
	territories.push_back(yakutsk_Terr);

	Mesh kamchatka = Mesh();
	kamchatka.Create(bufferData, indices, "BlankTile");
	kamchatka.SetModel(glm::translate(territoryEmptyScale, glm::vec3(40.0f, 25.0f, 0.0f)));
	Territory* kamchatka_Terr = new Territory("Kamchatka", kamchatka);
	territories.push_back(kamchatka_Terr);

	Mesh siberia = Mesh();
	siberia.Create(bufferData, indices, "BlankTile");
	siberia.SetModel(glm::translate(territoryEmptyScale, glm::vec3(20.0f, 22.0f, 0.0f)));
	Territory* siberia_Terr = new Territory("Siberia", siberia);
	territories.push_back(siberia_Terr);

	Mesh ural = Mesh();
	ural.Create(bufferData, indices, "BlankTile");
	ural.SetModel(glm::translate(territoryEmptyScale, glm::vec3(15.0f, 16.0f, 0.0f)));
	Territory* ural_Terr = new Territory("Ural", ural);
	territories.push_back(ural_Terr);

	Mesh afghanistan = Mesh();
	afghanistan.Create(bufferData, indices, "BlankTile");
	afghanistan.SetModel(glm::translate(territoryEmptyScale, glm::vec3(13.0f, 9.0f, 0.0f)));
	Territory* afghanistan_Terr = new Territory("Afghanistan", afghanistan);
	territories.push_back(afghanistan_Terr);

	Mesh japan = Mesh();
	japan.Create(bufferData, indices, "BlankTile");
	japan.SetModel(glm::translate(territoryEmptyScale, glm::vec3(43.0f, 10.0f, 0.0f)));
	Territory* japan_Terr = new Territory("Japan", japan);
	territories.push_back(japan_Terr);

	//Oceania Territories
	Mesh indonesia = Mesh();
	indonesia.Create(bufferData, indices, "BlankTile");
	indonesia.SetModel(glm::translate(territoryEmptyScale, glm::vec3(31.0f, -16.0f, 0.0f)));
	Territory* indonesia_Terr = new Territory("Indonesia", indonesia);
	territories.push_back(indonesia_Terr);

	Mesh westernAU = Mesh();
	westernAU.Create(bufferData, indices, "BlankTile");
	westernAU.SetModel(glm::translate(territoryEmptyScale, glm::vec3(37.0f, -26.0f, 0.0f)));
	Territory* westernAustrallia_Terr = new Territory("Western Australlia", westernAU);
	territories.push_back(westernAustrallia_Terr);

	Mesh easternAU = Mesh();
	easternAU.Create(bufferData, indices, "BlankTile");
	easternAU.SetModel(glm::translate(territoryEmptyScale, glm::vec3(46.0f, -25.0f, 0.0f)));
	Territory* easternAustrallia_Terr = new Territory("Eastern Australlia", easternAU);
	territories.push_back(easternAustrallia_Terr);

	Mesh newGuinea = Mesh();
	newGuinea.Create(bufferData, indices, "BlankTile");
	newGuinea.SetModel(glm::translate(territoryEmptyScale, glm::vec3(42.0f, -14.0f, 0.0f)));
	Territory* newGuinea_Terr = new Territory("New Guinea", newGuinea);
	territories.push_back(newGuinea_Terr);

	//North America adjacencies
	alaska_Terr->SetAdjacency({nwTerritories_Terr, alberta_Terr, kamchatka_Terr});
	nwTerritories_Terr->SetAdjacency({ alaska_Terr, alberta_Terr, greenland_Terr, ontario_Terr});
	alberta_Terr->SetAdjacency({ alaska_Terr, nwTerritories_Terr, ontario_Terr, westernUS_Terr});
	ontario_Terr->SetAdjacency({ alberta_Terr, nwTerritories_Terr, greenland_Terr, quebec_Terr, westernUS_Terr, easternUS_Terr});
	quebec_Terr->SetAdjacency({ ontario_Terr, easternUS_Terr, greenland_Terr});
	greenland_Terr->SetAdjacency({ nwTerritories_Terr, ontario_Terr, quebec_Terr, iceland_Terr});
	westernUS_Terr->SetAdjacency({ alberta_Terr, ontario_Terr, easternUS_Terr, centralAmerica_Terr});
	easternUS_Terr->SetAdjacency({ westernUS_Terr, ontario_Terr, quebec_Terr, centralAmerica_Terr});
	centralAmerica_Terr->SetAdjacency({ westernUS_Terr, easternUS_Terr, venezuela_Terr });

	//South America adjacencies
	venezuela_Terr->SetAdjacency({ centralAmerica_Terr, peru_Terr, brazil_Terr});
	peru_Terr->SetAdjacency({ venezuela_Terr, argentina_Terr, brazil_Terr});
	argentina_Terr->SetAdjacency({ peru_Terr, brazil_Terr});
	brazil_Terr->SetAdjacency({ peru_Terr, venezuela_Terr, argentina_Terr, northAfrica_Terr});
	
	//Africa adjacencies
	northAfrica_Terr->SetAdjacency({ brazil_Terr, westernEU_Terr, southernEU_Terr, egypt_Terr, congo_Terr, eastAfrica_Terr});
	egypt_Terr->SetAdjacency({ northAfrica_Terr, southernEU_Terr, middleEast_Terr, eastAfrica_Terr});
	eastAfrica_Terr->SetAdjacency({ northAfrica_Terr, egypt_Terr, middleEast_Terr, congo_Terr, madagascar_Terr, southAfrica_Terr});
	congo_Terr->SetAdjacency({ northAfrica_Terr, eastAfrica_Terr, southAfrica_Terr});
	southAfrica_Terr->SetAdjacency({ congo_Terr, eastAfrica_Terr, madagascar_Terr});
	madagascar_Terr->SetAdjacency({ southAfrica_Terr, eastAfrica_Terr});
	
	//Europe adjacencies
	iceland_Terr->SetAdjacency({greenland_Terr, scandinavia_Terr, uk_Terr});
	scandinavia_Terr->SetAdjacency({ iceland_Terr, northernEU_Terr, uk_Terr, ukraine_Terr});
	uk_Terr->SetAdjacency({ iceland_Terr, northernEU_Terr, scandinavia_Terr, westernEU_Terr});
	westernEU_Terr->SetAdjacency({uk_Terr, northernEU_Terr, southernEU_Terr, northAfrica_Terr });
	northernEU_Terr->SetAdjacency({ uk_Terr, westernEU_Terr, southernEU_Terr, ukraine_Terr, scandinavia_Terr});
	southernEU_Terr->SetAdjacency({ westernEU_Terr, northernEU_Terr, ukraine_Terr, northAfrica_Terr, egypt_Terr, middleEast_Terr});
	ukraine_Terr->SetAdjacency({ scandinavia_Terr, northernEU_Terr, southernEU_Terr, middleEast_Terr, afghanistan_Terr, ural_Terr });

	//Asia adjacencies
	middleEast_Terr->SetAdjacency({ southernEU_Terr, egypt_Terr, eastAfrica_Terr, india_Terr, afghanistan_Terr, ukraine_Terr });
	afghanistan_Terr->SetAdjacency({ middleEast_Terr, india_Terr, china_Terr, ural_Terr, ukraine_Terr });
	ural_Terr->SetAdjacency({ siberia_Terr, china_Terr, afghanistan_Terr, ukraine_Terr });
	siberia_Terr->SetAdjacency({ ural_Terr, china_Terr, irkutsk_Terr, yakutsk_Terr, mongolia_Terr });
	yakutsk_Terr->SetAdjacency({ siberia_Terr, irkutsk_Terr, kamchatka_Terr });
	kamchatka_Terr->SetAdjacency({ yakutsk_Terr, irkutsk_Terr, japan_Terr, alaska_Terr });
	japan_Terr->SetAdjacency({ mongolia_Terr, kamchatka_Terr });
	irkutsk_Terr->SetAdjacency({ mongolia_Terr, kamchatka_Terr, yakutsk_Terr, siberia_Terr });
	mongolia_Terr->SetAdjacency({ japan_Terr, kamchatka_Terr, irkutsk_Terr, siberia_Terr, china_Terr });
	china_Terr->SetAdjacency({ mongolia_Terr, siberia_Terr, ural_Terr, afghanistan_Terr, india_Terr, siam_Terr });
	india_Terr->SetAdjacency({ middleEast_Terr, afghanistan_Terr, china_Terr, siam_Terr });
	siam_Terr->SetAdjacency({ india_Terr, china_Terr, indonesia_Terr });

	//Oceania adjacencies
	indonesia_Terr->SetAdjacency({ siam_Terr, newGuinea_Terr, westernAustrallia_Terr });
	newGuinea_Terr->SetAdjacency({ indonesia_Terr, westernAustrallia_Terr, easternAustrallia_Terr });
	westernAustrallia_Terr->SetAdjacency({ indonesia_Terr, easternAustrallia_Terr, newGuinea_Terr });
	easternAustrallia_Terr->SetAdjacency({westernAustrallia_Terr, newGuinea_Terr });
}

void SetupWindow()
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

	map.Create(bufferData, indices, "map");
	SetUpTerritories(bufferData, indices);
}

void UpdateWindow() 
{
	mainWindow->Update();
	App::isRunning = !mainWindow->GetWindowShouldClose();

	map.Draw(shader);
	for (int i = 0; i < territories.size(); i++)
	{
		territories[i]->Draw(shader);
	}
}

void Start()
{
	std::srand(std::time(nullptr));
	territories = std::vector<Territory*>();
	SetupWindow();

	cout << "Please write a number of players between 2 to 2: \n";
	cin >> playerCount;

	for (int i = 0; i < playerCount; i++)
	{
		players.push_back(Player());
	}

	for (Territory* territory : territories)
	{
		territory->SetPlayerInControl(rand() % playerCount);
	}
}

void Update() 
{
	UpdateWindow();
}