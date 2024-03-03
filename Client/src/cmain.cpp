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

Window* mainWindow;
Shader shader;

Mesh northAmerica;
Mesh southAmerica;
Mesh eurasia;
Mesh africa;

Camera camera;

float height = 500;
float width = 500;

void Start()
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

void Update() 
{
	mainWindow->Update();
	App::isRunning = !mainWindow->GetWindowShouldClose();

	northAmerica.Draw(shader);
	southAmerica.Draw(shader);
	eurasia.Draw(shader);
	africa.Draw(shader);

	//camera.Update(view, *mainWindow);
}