#include <iostream>
#include <string>
#include <thread>

#include "gl/glew.h"
#include "gl/GL.h"
#include "GLFW/glfw3.h"

#include "Timer.h"
#include "Loader.h"
#include "App.h"
#include "Drawable.h"
#include "linmath.h"

App::App(int width, int height, std::string title) {
	this->sWidth = width;
	this->sHeight = height;
	this->sAppTitle = title;
	this->sTimer = Timer();
}

bool App::start() {

	std::string fragment_text = getFileContents("default.fragment");
	std::string vertex_text = getFileContents("default.vertex");

	if (!glfwInit()) {
		std::cout << "Error at : glfwInit()" << std::endl;
		return false;
	}

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

	Drawable test_drawable;

	init_shaders((char*)vertex_text.c_str(), (char*)fragment_text.c_str());

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
		sizeof(test_drawable.vertices[0]), (void*)0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(test_drawable.vertices[0]), (void*)(sizeof(float) * 2));

	loop();

	glfwTerminate();
	return true;
}

inline void App::init_shaders(char vertex_text[], char frag_text[]) {

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_text, NULL);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &frag_text, NULL);
	glCompileShader(fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	/*
	I don't what in the actual fuck the following means
	*/

	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vPos");
	vcol_location = glGetAttribLocation(program, "vCol");

}

void App::sync() {
	float loopSlot = 1.f / TARGET_FPS;
	double endTime = sTimer.getLastLoopTime();
	while (sTimer.getTime() < endTime) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void App::update(float delta) {

}

void App::render() {
	

	
}

void App::loop() {
	float elapsedTime;
	float accumulator = 0.f;
	float interval = 1.f / TARGET_FPS;

	while (!glfwWindowShouldClose(window)) {

		elapsedTime = sTimer.getElapsedTime();
		accumulator += elapsedTime;

		float ratio;
		int width, height;
		mat4x4 m, p, mvp;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		while (accumulator >= interval) {
			update(interval);
			accumulator -= interval;
		}

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		mat4x4_identity(m);
		mat4x4_rotate_Z(m, m, (float)glfwGetTime());
		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);

		glUseProgram(program);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		
		glfwPollEvents();

		sync();

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
