#include <vector>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Core/main.cpp"
#include "iostream"
#include "glm/glm.hpp"
#include "Window/Window.h"
#include "IO/FileReader.h"
#include "Mesh/Mesh.h"
#include "Shader/Shader.h"

Window* mainWindow;
Shader shader;
Mesh mesh;

float height = 500;
float width = 500;

glm::mat4 model = glm::mat4(1);
glm::mat4 view = glm::mat4(1);

void Start() 
{
	mainWindow = new Window(width, height, "Window");
	mainWindow->SetClearColour(0.0f, 0.0f, 0.0f, 1.0f);

	std::vector<char> fragSource = FileReader::ReadFile("Fragment");
	std::vector<char> vertSource = FileReader::ReadFile("Vertex");

	shader.Compile(vertSource, ShaderType::VERTEX);
	shader.Compile(fragSource, ShaderType::FRAGMENT);

	shader.Link();
	
	model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(100.0f, 0.0f, 100.0f));
	view = glm::translate(view, glm::vec3(0.0f, -2.0f, -2.0f));

	std::vector<glm::vec3> vertices =
	{
		{-0.5f, 0.0f, -0.5f},
		{0.5f, 0.0f, -0.5f},
		{0.0f, 0.0f, 0.5f}
	};

	std::vector<int> indices =
	{
		0, 1, 2
	};

	mesh.Create(vertices, indices);
	mesh.SetProjection(glm::perspective(90.0f, height/width, 0.1f, 1000.0f));
	mesh.SetView(view);
	mesh.SetModel(model);
}

void Update() 
{
	mainWindow->Update();
	App::isRunning = !mainWindow->GetWindowShouldClose();

	mesh.Draw(shader);
}