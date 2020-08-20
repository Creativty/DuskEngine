#pragma once
#include "GLFW/glfw3.h"
#include "Vectors.h"
#include "ShaderProgram.h"

struct Vertex {
	float x, y, z;
};

class Drawable {
public:
	Drawable();
	void draw(ShaderProgram &shader);
	void GenerateVertices();
	Vertex vertices[4] = {
		{ 0.5f, 0.5f, 0.0f },
		{  0.5f, -0.5f, 0.0f},
		{ - 0.5f, -0.5f, 0.0f},
		{  -0.5f,  0.5f, 0.0f }
	};

	unsigned int indices[6] = {
		0, 1, 3, 1, 2, 3
	};
private:
	Vec2D position;
	Vec2D size;
	Vec3D color;
	GLuint vboID, vaoID, eboID;
};