#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Racket.h"
#include <thread>
#include <chrono>
#include <cmath>
#include <string>
#include <list>


class Pong final 
{
public:
	explicit Pong();
	void RunGame();
	~Pong();
	const int windowWidth, windowHight;
	sf::RenderWindow windowOfGame;
private:	
	void DelayTime(long long ms = 1000);
	void RenderWindowGame();
	void ProcessEventsMadeByUser();
	void HandleUserInput(const sf::Keyboard::Key &key,bool isPressed);
	bool GameOver();
	void ResetScoreAndPosition();
	sf::Text *score_1;//score of racket_1
	sf::Text *score_2;//score of racket_2
	Racket racket_1;//lower position on window
	Racket racket_2;//upper position on window
	Ball bouncingElement;
	std::list<std::thread> thread;
};

