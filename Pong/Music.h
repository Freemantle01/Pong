#pragma once
#include <string>
#include <SFML/Audio.hpp>
namespace Game
{
	class Music final
	{
	public:
		explicit Music();
		~Music();
		sf::SoundBuffer racketHit;
		sf::SoundBuffer wallHit;
		sf::SoundBuffer fail;
		sf::Sound sound;
		void play(const sf::SoundBuffer& buffer);
	private:
		void loadFromFile(sf::SoundBuffer &buffer, const std::string &path);
		std::string file_path[3] = { "Music_samples/racket.wav",
								"Music_samples/wall.wav", 
								"Music_samples/fail.wav" };

	};
}


