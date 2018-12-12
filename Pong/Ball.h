#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2d.h"
#include <random>
#include "Music.h"
#include "Text.h"
#include "Racket.h"
#include <mutex>
#include <array>
#include <atomic>
#include "Color.h"

class Ball final
{
public:
	Ball() = delete;
	~Ball();
	explicit Ball(const int &width, const int &hight);
	void CheckCollisions(const Racket &racket);
	void Move(const Racket &racket_1, const Racket &racket_2);
	void CheckCollisionWithWalls();
	bool CheckCollisionWithRacket(const sf::RectangleShape &racket, const bool &upper_racket);
	void SetBallVectorHitByRacket(const bool &racketIsMovingLeft, const bool &racketIsMovingRight);
	void GenerateRandomDisplacmentVector();
	int GenerateRandomNumber(const unsigned int& from,const unsigned int& to);
	void UpdateColor();
	sf::CircleShape ball;
	Game::Text scoreOfRacket_1;//lower position on the window
	Game::Text scoreOfRacket_2;//upper position
	Vector2d VectorOfDisplacment;
	const int windowWidth, windowHight;
	Game::Color colorOfBall;
private:
	void CalculateDistance(bool lowerTheValue = false);
	void SetStartingPosition();
	float GetYPosition(const bool &upper_racket);
	void SetBasicParametersOfBall();
	const float diameterOfball = 20;
	float velocity = 300;
	const float time = 1.f / 60.f;
	float distance;
	Game::Music music;
	bool slowTheBall;
};
