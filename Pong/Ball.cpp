#include "Ball.h"



Ball::Ball(const int &windowWidth, const int &windowHight) :
	VectorOfDisplacment{ 1,-1 },
	windowWidth{ windowWidth }, windowHight{ windowHight },
	scoreOfRacket_1{ windowWidth,windowHight },
	scoreOfRacket_2{ windowWidth,windowHight, true },
	slowTheBall{ true },
	distance{0}
{
	CalculateDistance(true);
	SetBasicParametersOfBall();
}

Ball::~Ball()
{
}

void Ball::CheckCollisionWithWalls()
{
	float x = ball.getPosition().x;
	float y = ball.getPosition().y;
	float radius = ball.getRadius();
	//the position of ball is the center of circle
	if (y<=radius)//ball out of upper window
	{
		SetStartingPosition();
		++scoreOfRacket_1;
	}
	else if (y>=(windowHight-radius)&&y)//ball out of lower window
	{
		SetStartingPosition();
		++scoreOfRacket_2;
	}
	else if (x <= radius || x >= (windowWidth-radius))//contact with wall (left or right)
	{
		VectorOfDisplacment.x *= -1;
		music.play(music.wallHit);
		slowTheBall = false;
	}
}

void Ball::SetStartingPosition()
{
	music.play(music.fail);
	ball.setPosition(windowWidth / 2.f, windowHight / 2.f);
	GenerateRandomDisplacmentVector();
	slowTheBall = true;
}

bool Ball::CheckCollisionWithRacket(const sf::RectangleShape &racket, const bool &upper_racket)
{
	auto RacketPosition = racket.getPosition();
	float endXRacket = racket.getSize().x + RacketPosition.x;
	float xBall = ball.getPosition().x;
	float yBall = GetYPosition(upper_racket);
	if (RacketPosition.y==yBall)
	{
		if (xBall >= RacketPosition.x && xBall<=endXRacket)
		{
			music.play(music.racketHit);
			slowTheBall = false;
			return true;
		}
	}
	return false;
}

float Ball::GetYPosition(const bool &upper_racket)
{
	if (upper_racket) 
	{
		return ball.getPosition().y - ball.getRadius();
	}
	else 
	{
		return ball.getPosition().y + ball.getRadius();
	}
}

void Ball::CheckCollisions(const Racket &racket)
{
	bool left = racket.racketIsMovingLeft;
	bool right = racket.racketIsMovingRight;
	if (CheckCollisionWithRacket(racket.racket, racket.upper_position))
	{
		SetBallVectorHitByRacket(left, right);
	}
}

inline void Ball::CalculateDistance(bool lowerTheValue)
{
	if (lowerTheValue){
		distance = velocity * time * 0.4f;
	}
	else	{
		distance = velocity * time;
	}
}

void Ball::Move(const Racket &racket_1, const Racket &racket_2)
{
	CheckCollisionWithWalls();
	CheckCollisions(racket_1);
	CheckCollisions(racket_2);
	CalculateDistance(slowTheBall);
	ball.move(VectorOfDisplacment.x*distance, VectorOfDisplacment.y*distance);
	UpdateColor();
}

void Ball::UpdateColor()
{
	ball.setFillColor(sf::Color(colorOfBall.r, colorOfBall.g, colorOfBall.b, colorOfBall.alpha));
}

void Ball::SetBallVectorHitByRacket(const bool &racketIsMovingLeft, const bool &racketIsMovingRight)
{
	if (racketIsMovingLeft && !racketIsMovingRight && VectorOfDisplacment.x>0)
	{
		VectorOfDisplacment.y *= -1;
		VectorOfDisplacment.x *= -1;
	}
	else if (racketIsMovingRight && !racketIsMovingLeft && VectorOfDisplacment.x < 0)
	{
		VectorOfDisplacment.y *= -1;
		VectorOfDisplacment.x *= -1;
	}
	else
	{
		VectorOfDisplacment.y *= -1;
	}
}

void Ball::SetBasicParametersOfBall()
{
	ball.setRadius(diameterOfball/2);
	ball.setFillColor(sf::Color::Magenta);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
	ball.setPosition(windowWidth / 2.f, windowHight / 2.f);
}

void Ball::GenerateRandomDisplacmentVector()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1,2);
	if (dist(mt) == 1) 
	{
		VectorOfDisplacment.x = -1;
	}
	else 
	{
		VectorOfDisplacment.x = 1;
	}
	if (dist(mt) == 1) 
	{
		VectorOfDisplacment.y = -1;
	}
	else
	{
		VectorOfDisplacment.y = 1;
	}
}

int Ball::GenerateRandomNumber(const unsigned int & from, const unsigned int & to)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(from, to);
	return dist(mt);
}