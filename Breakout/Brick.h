#pragma once

#include "Sprite.h"

class Brick : public Sprite {
public:
	Brick(const Shader& shader, float x, float y, const std::vector<float>& vertices,
		float colorR, float colorG, float colorB);

	const std::vector<float>& getVertices() override { return vertices; };
	void render() const override;

	const float x;
	const float y;
	const float colorR;
	const float colorG;
	const float colorB;

	const std::vector<float>& vertices;
};

