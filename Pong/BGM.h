#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include  <string>
#include <array>
#include <iostream>
#include "Text.h"


class BGM
{
public:
	BGM() = delete;
	explicit BGM(const int &widthGame, const int &heightGame);
	void CreateWindow();
	~BGM();
private:
	void Run();
	void RenderWindow();
	void ProcessEventsMadeByUser();
	void HandleUserInput(const sf::Keyboard::Key &key, bool IsPressed);
	void OpenFromFile();
	void SetPoistionOfWindow();
	void CreateMenuText();
	const int widthWin{ 320 }, heightWin{ 240 };
	void GoUpCurrentOption();
	void GoDownCurrentOption();
	void PlayMusic();
	void StopMusic();
	void ChangeColorOfOption(sf::Color color);
	sf::RenderWindow *window{ nullptr };
	std::string folder_path{ "bgm/" };
	const std::array<std::string, 4> file_path{
		"Crystal-Caverns.wav", "Hypnotic-Puzzle.wav",
		"Monkey-Drama.wav", "Water-Balloon-Maniacs.wav"
	};
	std::array<sf::Music, 4> music;//size must be equal to amount of files
	int widthGame, heightGame;
	std::array<Game::Text, 4> options;
	int currentOption;
};

