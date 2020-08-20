#include <iostream>

#include "gl/glew.h"
#include "GLFW/glfw3.h"
#include "Drawable.h"
#include "ShaderProgram.h"

Drawable::Drawable() {
	this->position = { 0.0f, 0.0f };
	this->size = { 4.0f, 4.0f };
	this->color = { 0.75f, 0.0f, 1.0f };
	GenerateVertices();
}

void Drawable::GenerateVertices() {
	/*
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	*/

	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboID);
	glGenBuffers(1, &eboID);

	glBindVertexArray(vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Drawable::draw(ShaderProgram &shader) {
	std::cout << "Called Drawable::Draw" << std::endl;
	glUseProgram(shader.program);
	glBindVertexArray(vaoID);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}