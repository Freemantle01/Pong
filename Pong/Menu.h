#pragma once
#include "Pong.h"
#include <array>
namespace Game
{
	class Menu final
	{
	public:
		explicit Menu();
		~Menu();
	private:
		void ProcessEventsMadeByUser();
		void HandleUserInput(const sf::Keyboard::Key &key, bool isPressed);
		void RunMenu();
		void DisplayOptions();
		void SetAllTextData();
		void SetTextParameters();
		void SetTextLocation(sf::Text & text);
		void SetTextPosition();
		void SetHighlightColor();
		Pong game;
		sf::RenderWindow *window;
		std::array<Game::Text, 3> text;
		bool start_option;//this option is highlighted 
	};
}


