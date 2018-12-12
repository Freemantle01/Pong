#pragma once
#include <SFML/Graphics.hpp>

class Racket final
{
public:
	explicit Racket(const int &windowWidth, const int &windowHight, bool upper_position=false);
	~Racket();
	float CalculateDisplacmentRacket(const float &velocity, const float& time);
	void UpdateMovementOfRacket(const sf::Time &Time);
	bool HasRacketReachedEnd(const float &distanceX);
	bool racketIsMovingLeft;
	bool racketIsMovingRight;
	void SetUpperColor();
	void SetUpperRacketOrigin();
	sf::RectangleShape racket;
	bool upper_position;
	void SetLowerPosition();
	void SetUpperPosition();
private:
	void SetParametersOfRacket();
	const int windowWidth, windowHight;
	const float velocityOfRacket{ 400 };
	const float widthRect{ 100 }, heightRect { 10 };
};

