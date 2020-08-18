#pragma once
#include <string>
#include "GLFW/glfw3.h"
#include "Timer.h"

class App
{
public:
	App(int width, int height, std::string title);

	bool start();

	void setFrameRate(float rate);
	void loop();
	void update(float delta);
	void render();
	void sync();

	inline void init_shaders(char* vertex_text, char* frag_text);
	
private:

	GLFWwindow* window;
	GLuint vertex_shader, fragment_shader, program;
	GLint mvp_location, vpos_location, vcol_location;

	std::string sAppTitle;
	float TARGET_FPS = 60.f;
	int sWidth, sHeight;
	Timer sTimer;
};