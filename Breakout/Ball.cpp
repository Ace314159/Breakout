#include "stdafx.h"
#include "Ball.h"


Ball::Ball(const Shader& shader) : Sprite(shader) { addVertices(GL_DYNAMIC_DRAW); }

const std::vector<float>& Ball::getVertices() {
	vertices.push_back(0);
	vertices.push_back(0);
	for(int i = 1; i < numVertices; i++) {
		float angle = glm::radians(i * 360.0f / (numVertices - 1));
		vertices.push_back(radius * cos(angle));
		vertices.push_back(radius * sin(angle));
	}
	return vertices;
}

bool Ball::tick() {
	if(x - radius <= 0 || x + radius >= WINDOW_WIDTH) {
		xVel = -xVel;
	}
	if(y - radius <= 0) {
		yVel = -yVel;
	} else if(y + radius >= WINDOW_HEIGHT) {
		return false;
	}

	x += xVel;
	y += yVel;
	return true;
}

void Ball::render() const {
	shader.use();
	glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(x, y, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("color", 0, 0, 0.8f);

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLE_FAN, 0, numVertices);

	glBindVertexArray(0);
	glUseProgram(0);
}
