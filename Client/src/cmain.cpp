#include "Core/main.cpp"
#include "iostream"
#include "glm/glm.hpp"
#include "Window/Window.h"

Window* mainWindow;

void Start() 
{
	mainWindow = new Window(500, 500, "Window");
	mainWindow->SetClearColour(0.2f, 0.05f, 0.2f, 1.0f);
}

void Update() 
{
	mainWindow->Update();
	App::isRunning = !mainWindow->GetWindowShouldClose();
}