#include "stdafx.h"
#include "Game.h"


Game::Game(GLFWwindow* window) : window(window), spriteShader("sprite"), ball(spriteShader), paddle(spriteShader) {
	spriteShader.use();
	spriteShader.setMat4("projection", glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT,
		0.0f, 0.0f, 1.0f));
	glUseProgram(0);

	std::vector<float> vertices = {
		0, 0,
		0, brickHeight,
		brickWidth, 0,
		brickWidth, brickHeight
	};
	for(auto i : vertices) {
		cout << i << endl;
	}

	// Create rainbow of colors by converting from HSV to RGB
	float H;
	const float S = 0.86f;
	const float V = 0.61f;
	auto k = [S, V](float H, int n) { return std::fmod((n + H * 6), 6.0f); };
	auto f = [S, V, k](float H, int n) { return V - V * S *
		std::max(std::min({k(H, n), 4 - k(H, n), 1.0f}), 0.0f); };
	for(int j = 0; j < numBricksY; j++) {
		H = (float)j / numBricksY;
		for(int i = 0; i < numBricksX; i++) {
			bricks.push_back(std::make_unique<Brick>(spriteShader, brickWidth * i, brickHeight * j, vertices,
				f(H, 5), f(H, 3), f(H, 1)));
		}
	}
}

Game::~Game() {}

void Game::tick() {
	switch(state) {
	case GameState::START:
		start();
		break;
	case GameState::PLAY:
		play();
		break;
	case GameState::LOST:
		lost();
		break;
	}
}

void Game::start() {
	paddle.tick(window);
	ball.x = paddle.x + paddle.width / 2;
	ball.y = paddle.y - ball.radius;

	if(glfwGetKey(window, GLFW_KEY_SPACE)) {
		state = GameState::PLAY;
	}
}

void Game::play() {
	paddle.tick(window);
	bool playing = ball.tick();
	if(!playing) {
		state = GameState::LOST;
		return;
	}

	// Collision Detection
	bool collided = false;
	// Ball Paddle Collision
	float deltaX = ball.x - std::max(paddle.x, std::min(ball.x, paddle.x + paddle.width));
	float deltaY = ball.y - std::max(paddle.y, std::min(ball.y, paddle.y + paddle.height));
	collided = pow(deltaX, 2) + pow(deltaY, 2) < pow(ball.radius, 2);

	if(collided) {
		ball.yVel = -ball.yVel;
	}
	// Brick Ball Collision
	collided = false;
	auto it = std::remove_if(bricks.begin(), bricks.end(), [this](const std::unique_ptr<Brick>& brick) {
		float deltaX = ball.x - std::max(brick->x, std::min(ball.x, brick->x + brickWidth));
		float deltaY = ball.y - std::max(brick->y, std::min(ball.y, brick->y + brickHeight));
		return pow(deltaX, 2) + pow(deltaY, 2) < pow(ball.radius, 2);
	});
	auto prevSize = bricks.size();
	bricks.erase(it, bricks.end());
	if(bricks.size() < prevSize) {
		ball.yVel = -ball.yVel;
	}
}

void Game::lost() {

}

void Game::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	for(auto const& brick : bricks) {
		brick->render();
	}
	paddle.render();
	ball.render();

}
