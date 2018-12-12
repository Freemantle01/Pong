#include "Text.h"



Game::Text::Text(const int width, const int hight):score{0}
{
	if (font.loadFromFile("Fonts/OpenSans-Light.ttf"))
	{
		text.setFont(font);
		text.setCharacterSize(30);
		text.setPosition(static_cast<float>(width - 50), 
			static_cast<float>(hight - 50));
		text.setFillColor(sf::Color::Green);
		text.setStyle(sf::Text::Bold);
		text.setString(std::to_string(score));
	}
}

void Game::Text::LoadFont()
{
	if (font.loadFromFile("Fonts/OpenSans-Light.ttf"))
	{
		text.setFont(font);
	}
}

sf::Text & Game::Text::GetText()
{
	return text;
}

Game::Text::Text(const int width, const int hight, const bool upper_position):
	Text(width,hight)
{
	if (upper_position)	{
		text.setPosition(static_cast<float>(width - 50), 20.f);
		text.setFillColor(sf::Color::Cyan);
	}
}

void Game::Text::operator++()
{
	++score;
	text.setString(std::to_string(score));
}

void Game::Text::operator++(int)
{
	++score;
	text.setString(std::to_string(score));
}

void Game::Text::operator--()
{
	--score;
	text.setString(std::to_string(score));
}

void Game::Text::operator--(int)
{
	--score;
	text.setString(std::to_string(score));
}

int* Game::Text::GetScore()
{
	return &score;
}

Game::Text::~Text()
{
}

Game::Text::Text(): score{0}
{
	LoadFont();
}