#include "Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "iostream";

void OnResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char* name) 
{
	m_width = width;
	m_height = height;

	if (!glfwInit()) {
		std::cout << "Error, failed to initialize GLFW library \n";
	}
	else
	{
		std::cout << "Successfully initialized GLFW library \n";
	}

	m_window = glfwCreateWindow(width, height, name, nullptr, nullptr);
	if (m_window == nullptr)
	{
		std::cout << "Error, failed to create window \n";
	}
	else
	{
		std::cout << "Successfully created GLFW window \n";
	}
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Error, ailed to initialize GLAD \n";
	}
	else
	{
		std::cout << "Successfully initialized GLAD \n";
	}

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(m_window, OnResize);
}

bool Window::GetWindowShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

bool Window::GetKeyDown(int keyCode)
{
	return glfwGetKey(m_window, keyCode) == GLFW_PRESS;
}

bool Window::GetMouseButtonDown(int mouseButton)
{
	return glfwGetMouseButton(m_window, mouseButton) == GLFW_PRESS;
}


void Window::SetCursorInputMode(int cursorState)
{
	glfwSetInputMode(m_window, GLFW_CURSOR, cursorState);
}

void Window::GetCursorPosition(double& x, double& y)
{
	glfwGetCursorPos(m_window, &x, &y);
}

void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);

	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(m_window, true);
	}

	glClearColor(clearColourR, clearColourG, clearColourB, clearColourA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}