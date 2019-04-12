#pragma once
#include "Sprite.h"
class Ball : public Sprite {
public:
	Ball(const Shader& shader);

	const std::vector<float>& getVertices() override;
	bool tick();
	void render() const override;

	const float radius = 10;

	float x = 200; // Center x
	float y = 200; // Ceneter y
	float xVel = 5;
	float yVel = 5;

	static const int numVertices = 361;
	std::vector<float> vertices;
};

