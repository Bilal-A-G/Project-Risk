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

#include "Player/Player.cpp";

using namespace std;

Window* mainWindow;
Shader shader;

Mesh northAmerica;
Mesh southAmerica;
Mesh eurasia;
Mesh africa;

Camera camera;

float height = 500;
float width = 500;

void CreateBoard();
vector<Player*> players;
int playerCount = 0;
int playerTurn = 0;

bool onePicked = false;
bool twoPicked = false;
bool threePicked = false;
bool fourPicked = false;

void Start()
{
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

	for (int i = 0; i < playerCount; ++i)
	{
		players.push_back(new Player());
	}

	for (int i = 0; i < players.size(); ++i)
	{
		int territoryNum = rand() % 4 + 1;

		switch (territoryNum)
		{
			case 1:
				if (onePicked == false)
				{
					//assign northAmerica territory here players[i].territories something something
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
					//assign southAmerica territory here players[i].territories something something
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
					//assign eurasia territory here players[i].territories something something
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
					//assign africa territory here players[i].territories something something
					fourPicked = true; // makes sure africa doesn't get assigned to more than one person
				}
				else
				{
					i--; // if the number was already picked, reset i so that it doesn't skip over the player and assigns a new number
					break;
				}
				break;
		}
	}

	CreateBoard();
}

void Update() 
{
	mainWindow->Update();
	App::isRunning = !mainWindow->GetWindowShouldClose();

	northAmerica.Draw(shader);
	southAmerica.Draw(shader);
	eurasia.Draw(shader);
	africa.Draw(shader);

	//camera.Update(view, *mainWindow);

	switch (playerTurn)
	{
		case 0: // player 1 turn
			cout << "\nPlayer 1's Turn.\n";
			players[0]->Reinforcement();
			players[0]->Attack();
			players[0]->Fortificate();

			playerTurn = 1; // set to player 2 turn
			
			break;
		case 1: // player 2 turn
			cout << "\nPlayer 2's Turn.\n";
			players[1]->Reinforcement();
			players[1]->Attack();
			players[1]->Fortificate();

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
			players[2]->Fortificate();

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
			players[3]->Fortificate();

			playerTurn = 0; // set to player 1 turn
			break;
	}
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


	std::vector<glm::vec3> vertices =
	{
		{0.0f,  0.0f, 0.0f},
		{0.0f, 0.5f, 0.0f},
		{0.5f, 0.0f, 0.0f},
		{0.5f, 0.5f, 0.0f},
	};

	std::vector<int> indices =
	{
		0, 1, 2,
		3, 1, 2,
	};

	northAmerica.Create(vertices, indices);
	southAmerica.Create(vertices, indices);
	eurasia.Create(vertices, indices);
	africa.Create(vertices, indices);

	northAmerica.SetModel(glm::translate(glm::mat4(1), glm::vec3(-0.6, 0.3f, 0.0f)));
	southAmerica.SetModel(glm::translate(glm::mat4(1), glm::vec3(-0.6, -0.5f, 0.0f)));
	eurasia.SetModel(glm::translate(glm::mat4(1), glm::vec3(0.3, 0.3f, 0.0f)));
	africa.SetModel(glm::translate(glm::mat4(1), glm::vec3(0.3, -0.6f, 0.0f)));
}

void Player::Reinforcement()
{
	cout << "\nreinforcement";
}

void Player::Attack()
{
	cout << "\nattack";
}

void Player::Fortificate()
{
	cout << "\nfortificate";
}