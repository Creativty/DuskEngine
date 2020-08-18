#pragma once
#include "GLFW/glfw3.h"
#include "Vectors.h"
class Drawable {
public:
	Drawable();
	void draw();

	const struct {
		float x, y;
		float r, g, b;
	} vertices[3] = {
		{ -0.6f, -0.4f, 1.f, 0.f, 0.f },
		{  0.6f, -0.4f, 0.f, 1.f, 0.f },
		{   0.f,  0.6f, 0.f, 0.f, 1.f }
	};
private:
	Vec2D position;
	Vec2D size;
	Vec3D color;
	GLuint vertex_buffer;
};