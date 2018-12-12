#include "Music.h"



Game::Music::Music()
{
	loadFromFile(racketHit, file_path[0]);
	loadFromFile(wallHit, file_path[1]);
	loadFromFile(fail, file_path[2]);
}

void Game::Music::loadFromFile(sf::SoundBuffer &buffer, const std::string &path)
{
	if (buffer.loadFromFile(path)){

	}
}

void Game::Music::play(const sf::SoundBuffer &buffer)
{
	if (buffer.getDuration().asMicroseconds()>0)
	{
		sound.setBuffer(buffer);
		sound.setVolume(20);
		sound.play();
	}
}

Game::Music::~Music()
{
}
