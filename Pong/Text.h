#pragma once
#include <SFML/Graphics.hpp>
#include <string>
namespace Game
{
	class Text final
	{
	public:
		explicit Text();
		explicit Text(const int width,const int hight);
		explicit Text(const int width, const int hight, const bool upper_position);
		void operator++();
		void operator++(int);
		void operator--();
		void operator--(int);
		int* GetScore();
		sf::Text& GetText();
		~Text();
		sf::Text text;
	private:
		void LoadFont();
		sf::Font font;
		int score;
	};
}


