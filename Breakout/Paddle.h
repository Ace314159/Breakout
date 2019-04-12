#pragma once

#include "Sprite.h"


class Paddle : public Sprite {
public:
	Paddle(const Shader& shader);

	const std::vector<float>& getVertices() override { return vertices; };
	void tick(GLFWwindow* window);
	void render() const override;

	const float width = 120;
	const float height = 20;

	float x = 400 - width / 2; // Top left x
	float y = 580 - height; // Top left y

	std::vector<float> vertices = {
		0, 0,
		0, height,
		width, 0,
		width, height
	};
};

