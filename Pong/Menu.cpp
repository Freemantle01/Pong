#include "Menu.h"



Game::Menu::Menu() :game(), start_option{true},
		text{  {Text(),Text(),Text()} },window{&game.windowOfGame}
{
	SetAllTextData();
	RunMenu();
}

void Game::Menu::RunMenu()
{
	while (window->isOpen())
	{
		ProcessEventsMadeByUser();
		DisplayOptions();
	}
}

void Game::Menu::ProcessEventsMadeByUser()
{
	sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				HandleUserInput(event.key.code, true);
				break;
			case sf::Event::Closed:
				game.windowOfGame.close();
				break;
			}
		}
}

void Game::Menu::HandleUserInput(const sf::Keyboard::Key &key, bool isPressed)
{
	if (key == sf::Keyboard::W || key == sf::Keyboard::Up ||
		key == sf::Keyboard::S || key == sf::Keyboard::Down)
	{
		start_option = !start_option;
		SetHighlightColor();
	}
	if (key==sf::Keyboard::Enter && start_option==true)
	{
		game.RunGame();
	}
	if (key==sf::Keyboard::Enter && start_option==false)
	{
		window->close();
	}
}

void Game::Menu::SetHighlightColor()
{
	if (start_option)
	{
		text[0].text.setFillColor(sf::Color::White);//"end"
		text[1].text.setFillColor(sf::Color::Green);//"start
	}
	else
	{
		text[0].text.setFillColor(sf::Color::Green);//"end"
		text[1].text.setFillColor(sf::Color::White);//"start
	}
}

void Game::Menu::SetAllTextData()
{
	SetTextParameters();
	for (size_t i = 0; i < text.size(); i++)
	{
		SetTextLocation(text[i].text);
	}
	SetTextPosition();
}

void Game::Menu::DisplayOptions()
{
	window->clear();
	for (size_t i = 0; i < text.size(); i++)
	{
		window->draw(text[i].text);
	}
	window->display();
}

void Game::Menu::SetTextParameters()
{
	for (int i = 0; i < text.size()-1; i++)
	{
		text[i].text.setCharacterSize(20);
		text[i].text.setFillColor(sf::Color::White);
		text[i].text.setStyle(sf::Text::Bold);
	}
	text[1].text.setFillColor(sf::Color::Green);
	text[2].text.setCharacterSize(40);
	text[2].text.setFillColor(sf::Color::Green);
	text[2].text.setStyle(sf::Text::Bold);
	text[0].text.setString("End");
	text[1].text.setString("Start");
	text[2].text.setString("Pong");
}

void Game::Menu::SetTextLocation(sf::Text & text)
{
	sf::FloatRect rect = text.getLocalBounds();
	text.setOrigin(rect.left + rect.width / 2.f,
					rect.top + rect.height / 2.f);
}

void Game::Menu::SetTextPosition()
{
	for (int i = 0; i < text.size()-1; i++)//set position of "end", "start"
	{
		text[i].text.setPosition(static_cast<float>(game.windowWidth) / 2.f,
			static_cast<float>(game.windowHight / 2.f - 40 * i));
	}
	text[2].text.setPosition(static_cast<float>(game.windowWidth) / 2.f,
		static_cast<float>(game.windowHight*0.2) );
}

Game::Menu::~Menu()
{
	
}
