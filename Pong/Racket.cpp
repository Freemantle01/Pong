#include "Racket.h"



Racket::Racket(const int &windowWidth, const int &windowHight, bool upper_position):
	windowWidth{windowWidth}, windowHight{windowHight},
	racketIsMovingLeft{false},racketIsMovingRight{false},
	upper_position{upper_position}
{
	SetParametersOfRacket();
	if (upper_position){
		SetUpperColor();
		SetUpperPosition();
	}
}

void Racket::SetUpperColor()
{
	racket.setFillColor(sf::Color::Cyan);
}

void Racket::SetUpperPosition()
{
	float x = (windowWidth - widthRect) / 2;
	float y = heightRect + 20;
	SetUpperRacketOrigin();
	racket.setPosition(x, y);
}

void Racket::SetUpperRacketOrigin()
{
	racket.setOrigin(0, heightRect);
}

Racket::~Racket()
{
}

void Racket::SetLowerPosition()
{
	float positionXRect = (windowWidth - widthRect) / 2;
	float positionYRect = windowHight - heightRect - 20;
	racket.setPosition(positionXRect, positionYRect);
}

void Racket::SetParametersOfRacket()
{
	SetLowerPosition();
	racket.setSize(sf::Vector2f{ widthRect, heightRect });
	racket.setFillColor(sf::Color::Green);
}

void Racket::UpdateMovementOfRacket(const sf::Time &time)
{
	float distanceX{ 0 };
	if (racketIsMovingLeft)
	{
		distanceX = CalculateDisplacmentRacket(velocityOfRacket, time.asSeconds());
		distanceX *= -1;
		if (!HasRacketReachedEnd(distanceX))
			racket.move(distanceX, 0);
	}
	if (racketIsMovingRight)
	{
		distanceX = CalculateDisplacmentRacket(velocityOfRacket, time.asSeconds());
		if (!HasRacketReachedEnd(distanceX))
			racket.move(distanceX, 0);
	}
}

bool Racket::HasRacketReachedEnd(const float &distanceX)
{
	auto currentX = (racket.getPosition()).x;
	auto currentY = (racket.getPosition()).y;
	auto widthRacket = (racket.getSize()).x;//cause we know the upper left position of racket
	if ((currentX + distanceX) < 0)
	{
		racket.setPosition(0.f, currentY);
		return true;
	}
	else if ((currentX + distanceX + widthRacket) > windowWidth)
	{
		racket.setPosition(static_cast<float>(windowWidth - widthRacket),
			currentY);
		return true;
	}
	return false;
}

inline float Racket::CalculateDisplacmentRacket(const float &velocity, const float &time)
{
	return velocity*time;
}