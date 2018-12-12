#include "Pong.h"

using  chrono = std::chrono::high_resolution_clock;
using ms_time = std::chrono::milliseconds;

Pong::Pong() :
	windowWidth{ 1280 }, windowHight{ 720 },
	windowOfGame{ sf::VideoMode(windowWidth,windowHight),"Pong" },
	bouncingElement(windowWidth, windowHight),
	racket_1{ windowWidth,windowHight },
	racket_2{ windowWidth,windowHight,true }
{	
	score_1=&bouncingElement.scoreOfRacket_1.text;
	score_2=&bouncingElement.scoreOfRacket_2.text;
}

bool Pong::GameOver()
{
	int *score1 = bouncingElement.scoreOfRacket_1.GetScore();
	int *score2 = bouncingElement.scoreOfRacket_2.GetScore();
	int difference =abs( *score1 - *score2);
	if ((*score1>=11 || *score2>=11 ) && difference>=2)
	{
		*score1 = 0;
		*score2 = 0;
		ResetScoreAndPosition();
		return false;
	}
	else
	{
		return true;
	}
}

void Pong::ResetScoreAndPosition()
{
	score_1->setString(std::to_string(0));
	score_2->setString(std::to_string(0));
	racket_1.SetLowerPosition();
	racket_2.SetUpperPosition();
	DelayTime(2000);
}

void Pong::RunGame()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	while (windowOfGame.isOpen() && GameOver())
	{
		timeSinceLastUpdate += clock.restart();
		ProcessEventsMadeByUser();
		if (timeSinceLastUpdate>TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			racket_1.UpdateMovementOfRacket(TimePerFrame);
			racket_2.UpdateMovementOfRacket(TimePerFrame);
			bouncingElement.Move(racket_1, racket_2);
		}
		RenderWindowGame();
	}
}

Pong::~Pong()
{
	for (auto& th:thread)
	{
		if (th.joinable())
		{
			th.join();
		}
	}
}

void Pong::RenderWindowGame()
{
	windowOfGame.clear();
	windowOfGame.draw(*score_1);
	windowOfGame.draw(*score_2);
	windowOfGame.draw(racket_1.racket);
	windowOfGame.draw(bouncingElement.ball);
	windowOfGame.draw(racket_2.racket);
	windowOfGame.display();
}

void Pong::DelayTime(long long ms)
{
	chrono::time_point start = chrono::now();
	chrono::time_point end;
	ms_time elapsed{ 0 };
	do
	{
		end = chrono::now();
		elapsed = std::chrono::duration_cast<ms_time>(end - start);
	} while (ms>elapsed.count());
}

void Pong::ProcessEventsMadeByUser()
{
	sf::Event event;
	while (windowOfGame.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			HandleUserInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			HandleUserInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			windowOfGame.close();
			break;
		}
	}
}

void Pong::HandleUserInput(const sf::Keyboard::Key &key, bool isPressed)
{
	if (key==sf::Keyboard::Left )
	{
		racket_1.racketIsMovingLeft = isPressed;
	}
	else if (key == sf::Keyboard::Right)
	{
		racket_1.racketIsMovingRight = isPressed;
	}

	if (key == sf::Keyboard::A)
	{
		racket_2.racketIsMovingLeft = isPressed;
	}
	else if (key == sf::Keyboard::D)
	{
		racket_2.racketIsMovingRight = isPressed;
	}
	
	if (key == sf::Keyboard::H)
	{
		thread.push_back(std::move(std::thread(&Game::Color::ChangeRGB,std::ref(bouncingElement.colorOfBall))));
	}
}

