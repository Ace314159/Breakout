#pragma once

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

class Game {
public:
	GLFWwindow* window;

	const int numBricksX = 20;
	const int numBricksY = 5;
	const float brickWidth = (float)WINDOW_WIDTH / numBricksX;
	const float brickHeight = 0.3f * WINDOW_HEIGHT / numBricksY;

	Shader spriteShader;
	Ball ball;
	Paddle paddle;
	std::vector<std::unique_ptr<Brick>> bricks;

	enum class GameState { START, PLAY, LOST };
	GameState state = GameState::START;

	Game(GLFWwindow* window);
	~Game();

	void tick();
	void start();
	void play();
	void lost();
	void render();
};

