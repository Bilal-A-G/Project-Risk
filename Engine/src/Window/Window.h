#pragma once

struct GLFWwindow;

class Window
{
public:
	Window(int width, int height, const char* name);
	void SetClearColour(float r, float g, float b, float a) 
	{
		clearColourR = r;
		clearColourG = g;
		clearColourB = b;
		clearColourA = a;
	}
	void Update();
	bool GetWindowShouldClose();
	bool GetKeyDown(int keyCode);
	bool GetMouseButtonDown(int mouseButton);
	void SetCursorInputMode(int cursorState);
	void GetCursorPosition(double& x, double& y);
private:
	int m_width;
	int m_height;
	float clearColourR;
	float clearColourG;
	float clearColourB;
	float clearColourA;
	GLFWwindow* m_window;
};

