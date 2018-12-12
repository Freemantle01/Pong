#include "BGM.h"



BGM::BGM(const int &widthGame, const int &heightGame):
	currentOption{0}, widthGame{widthGame}, heightGame{heightGame}
{
	OpenFromFile();
	CreateMenuText();
	PlayMusic();
}

void BGM::CreateMenuText()
{
	for (int i = 0; i < options.size(); i++)
	{
		std::string display_text = file_path[i].substr(0, file_path[i].size() - 4);//deleting the .wav
		options[i].text.setCharacterSize(20);
		options[i].text.setStyle(sf::Text::Bold);
		options[i].text.setString(display_text);
		options[i].text.setPosition(0,i*30);
		if (i==0){
			options[i].text.setFillColor(sf::Color::Green);
		}
		else{
			options[i].text.setFillColor(sf::Color::White);
		}
	}
}

void BGM::CreateWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(widthWin, heightWin), "Background music");
	SetPoistionOfWindow();
	Run();
}

void BGM::Run()
{
	while (window->isOpen())
	{
		ProcessEventsMadeByUser();
		RenderWindow();
	}
	StopMusic();//stoping the music after closing the window
}

void BGM::SetPoistionOfWindow()
{
	sf::Vector2i position=window->getPosition();
	position.x += widthGame/2 + widthWin/2;
	position.y += -heightGame/2 +heightWin/2;
	window->setPosition(position);
}

void BGM::RenderWindow()
{
	window->clear();
	for (auto menu:options)
	{
		window->draw(menu.text);
	}
	window->display();
}

void BGM::HandleUserInput(const sf::Keyboard::Key & key, bool IsPressed)
{
	if (key == sf::Keyboard::Up || key == sf::Keyboard::W)
	{
		StopMusic();
		GoUpCurrentOption();
		PlayMusic();
	}
	if (key == sf::Keyboard::Down || key == sf::Keyboard::S)
	{
		StopMusic();
		GoDownCurrentOption();
		PlayMusic();
	}
}

void BGM::PlayMusic()
{
	music[currentOption].play();
}

void BGM::StopMusic()
{
	music[currentOption].stop();
}

void BGM::GoUpCurrentOption()
{
	ChangeColorOfOption(sf::Color::White);
	if ( currentOption == 0 ){
		currentOption = options.size() - 1;
	}
	else {
		currentOption -= 1;
	}
	ChangeColorOfOption(sf::Color::Green);
}

void BGM::GoDownCurrentOption()
{
	ChangeColorOfOption(sf::Color::White);
	if (currentOption == (options.size() - 1)) {
		currentOption = 0;
	}
	else {
		currentOption += 1;
	}
	ChangeColorOfOption(sf::Color::Green);
}

void BGM::ChangeColorOfOption(sf::Color color)
{
	options[currentOption].text.setFillColor(color);
}

void BGM::ProcessEventsMadeByUser()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type){
		case sf::Event::Closed:	
		{
			window->close();
			break;
		}
		case sf::Event::KeyPressed:
		{
			HandleUserInput(event.key.code,true);
			break;
		}
		}
	}
}

BGM::~BGM()
{
	delete window;
}

void BGM::OpenFromFile()
{
	
	for (int i = 0; i < file_path.size(); i++)
	{
		if (!music[i].openFromFile(folder_path+file_path[i])){

		}
		else {
			music[i].setVolume(10.f);
				music[i].setLoop(true);
		}
	}
}