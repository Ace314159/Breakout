#include "stdafx.h"
#include "Brick.h"


Brick::Brick(const Shader& shader, float x, float y, const std::vector<float>& vertices,
	float colorR, float colorG, float colorB) : Sprite(shader), x(x), y(y), vertices(vertices),
	colorR(colorR), colorG(colorG), colorB(colorB) { addVertices(GL_STATIC_DRAW); }

void Brick::render() const {
	shader.use();
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("color", colorR, colorG, colorB);


	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
	glUseProgram(0);
}