#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include "BGM.h"



int main()
{
	const int GameWindowWidth{ 1280 };
	const int GameWindowHeight{ 720 };
	BGM music{ GameWindowWidth,GameWindowHeight };
	std::thread start_bgm(&BGM::CreateWindow,std::ref(music));
	auto start = std::make_shared<Game::Menu>();
	start_bgm.join();
	return 0;
}