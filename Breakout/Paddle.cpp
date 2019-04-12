#include "stdafx.h"
#include "Paddle.h"


Paddle::Paddle(const Shader& shader) : Sprite(shader) { addVertices(GL_DYNAMIC_DRAW); }

void Paddle::tick(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_RIGHT) && x + width < 800) {
		x += 5;
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT) && x > 0) {
		x -= 5;
	}
}

void Paddle::render() const {
	shader.use();
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("color", 0.5f, 0, 0);

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
	glUseProgram(0);
}
