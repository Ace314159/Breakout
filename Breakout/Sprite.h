#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"


class Sprite {
protected:
	GLuint VAO;
	GLuint VBO;
	const Shader& shader;
public:
	Sprite(const Shader& shader);
	~Sprite();

	virtual const std::vector<float>& getVertices() = 0;
	virtual void render() const = 0;

	void addVertices(GLenum usage);
};

