#include <iostream>
#include <string>
#include <thread>

#include "gl/glew.h"
#include "gl/GL.h"
#include "GLFW/glfw3.h"

#include "Timer.h"
#include "Loader.h"
#include "App.h"
#include "ShaderProgram.h"
#include "Drawable.h"
#include "linmath.h"

App::App(int width, int height, std::string title) {
	this->sWidth = width;
	this->sHeight = height;
	this->sAppTitle = title;
	this->sTimer = Timer();
}

bool App::start() {

	if (!glfwInit()) {
		std::cout << "Error at : glfwInit()" << std::endl;
		return false;
	}

	glfwDefaultWindowHints();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(sWidth, sHeight, sAppTitle.c_str(), NULL, NULL);
	if (!window) {
		std::cout << "Error at : glfwCreateWindow()" << std::endl;
		glfwTerminate();
		return false;
	}

	

	glfwMakeContextCurrent(window);

	/*
		ALWAYS MAKE SURE GLEW IS INITIALIZED AFTER OPENGL CONTEXT IS SET !
		GLEW WAS NEEDED FOR glCreateShader at first since it doesn't come out of package with glfw3 on windows !
	*/

	GLenum err = glewInit();

	if (GLEW_OK != err) {
		std::cout << "Error at : glewInit()" << std::endl;
		return false;
	}

	glfwSwapInterval(1);

	std::string fragment_text = getFileContents("default.fragment");
	std::string vertex_text = getFileContents("default.vertex");

	active_shader = ShaderProgram(vertex_text.c_str(), fragment_text.c_str());

	Drawable first_drawable, second_drawable;
	/*second_drawable.vertices[0] = { 0.3f, -0.1f, 1.f, 0.f, 0.f };
	second_drawable.vertices[1] = { 0.5f, -0.1f, 1.f, 0.f, 0.f };
	second_drawable.vertices[2] = { 0.5f, -0.3f, 1.f, 0.f, 0.f };
	second_drawable.GenerateVertices();*/

	Drawable drawables[2] = { first_drawable, second_drawable };

	loop(drawables);

	glfwTerminate();
	return true;
}

void App::sync() {
	float loopSlot = 1.f / TARGET_FPS;
	double endTime = sTimer.getLastLoopTime();
	while (sTimer.getTime() < endTime) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void App::update(float delta) {
	glfwSwapBuffers(window);

	glfwPollEvents();
}

void App::render(Drawable drawables[]) {
	
	float ratio;
	int width, height;
	mat4x4 m, p, mvp;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	//glViewport(0, 0, width, height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	drawables[0].draw(active_shader);
	
}

void App::loop(Drawable drawables[]) {
	float elapsedTime;
	float accumulator = 0.f;
	float interval = 1.f / TARGET_FPS;
	glViewport(0, 0, sWidth, sHeight);
	while (!glfwWindowShouldClose(window)) {

		//elapsedTime = sTimer.getElapsedTime();
		//accumulator += elapsedTime;
		render(drawables);
		//while (accumulator >= interval) {
			update(interval);
			//accumulator -= interval;
		//}

		
		
		//sync();

	}

}

void App::setFrameRate(float rate) {
	if (rate <= 240.f) {
		TARGET_FPS = rate;
	}
	else {
		TARGET_FPS = 60.f;
	}
}
