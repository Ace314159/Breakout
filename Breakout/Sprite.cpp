#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite(const Shader& shader) : shader(shader) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void Sprite::addVertices(GLenum usage) {
	const std::vector<float>& vertices = getVertices();

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), usage);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Sprite::~Sprite() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
