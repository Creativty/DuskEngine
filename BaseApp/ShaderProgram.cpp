#include <iostream>
#include "gl/glew.h"
#include "gl/gl.h"
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
	vertex_shader = 0;
	fragment_shader = 0;
	program = 0;

}

ShaderProgram::ShaderProgram(const char* vertex_text, const char* fragment_text) {

	int success;
	char infoLog[512];

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_text, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "ERROR COMPILING VERTEX SHADER : " << infoLog << std::endl;
	}

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_text, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cout << "ERROR COMPILING FRAGMENT SHADER : " << infoLog << std::endl;
	}

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR LINKING PROGRAM : " << infoLog << std::endl;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	/*
	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vPos");
	vcol_location = glGetAttribLocation(program, "vCol");
	*/

}

ShaderProgram::~ShaderProgram() {
	unbind();
	if (program != 0) {
		glDeleteProgram(program);
		
	}
}

void ShaderProgram::bind() {
	glUseProgram(program);
}

void ShaderProgram::unbind() {
	glUseProgram(program);
}