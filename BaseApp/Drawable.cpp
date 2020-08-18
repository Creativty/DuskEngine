#include "gl/glew.h"
#include "GLFW/glfw3.h"
#include "Drawable.h"

Drawable::Drawable() {
	this->position = { 0.0f, 0.0f };
	this->size = { 4.0f, 4.0f };
	this->color = { 0.75f, 0.0f, 1.0f };
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Drawable::draw() {
	glDrawArrays(GL_TRIANGLES, 0, 3);
}