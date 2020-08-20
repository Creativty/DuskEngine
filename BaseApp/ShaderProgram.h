#pragma once
#include "gl/gl.h"

#include "GLFW/glfw3.h"

class ShaderProgram {
public:
	
	GLuint vertex_shader, fragment_shader, program;
	//GLint mvp_location, vpos_location, vcol_location;

	ShaderProgram();
	~ShaderProgram();
	ShaderProgram(const char* vertex_text, const char* fragment_text);

	void bind();

	void unbind();
};