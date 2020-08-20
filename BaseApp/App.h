#pragma once
#include <string>
#include "GLFW/glfw3.h"
#include "Timer.h"
#include "ShaderProgram.h"
#include "Drawable.h";

class App
{
public:
	App(int width, int height, std::string title);

	bool start();

	void setFrameRate(float rate);
	void loop();
	void loop(Drawable drawables[]);
	void update(float delta);
	void render(Drawable drawables[]);
	void sync();

	//inline void init_shaders(char* vertex_text, char* frag_text);
	
private:

	GLFWwindow* window;
	ShaderProgram active_shader;

	std::string sAppTitle;
	float TARGET_FPS = 60.f;
	int sWidth, sHeight;
	Timer sTimer;
};