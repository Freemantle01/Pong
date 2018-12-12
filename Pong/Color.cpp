#include "Color.h"


using  chrono = std::chrono::high_resolution_clock;
using ms_time = std::chrono::milliseconds;

Game::Color::Color():r{192},g{52},b{222},alpha{255}
{
}


int Game::Color::GenerateRandomNumber(const unsigned int & from, const unsigned int & to)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(from, to);
	return dist(mt);
}

void Game::Color::ChangeRGB()
{
	mutex.lock(); 
	for (int i = 0; i < 5; i++)
	{
		r = GenerateRandomNumber(0, 255);
		g = GenerateRandomNumber(0, 255);
		b = GenerateRandomNumber(0, 255);
		DelayTime(200);
	}
	mutex.unlock();
}

void Game::Color::DelayTime(long long ms)
{
	chrono::time_point start = chrono::now();
	chrono::time_point end;
	ms_time elapsed{ 0 };
	do
	{
		end = chrono::now();
		elapsed = std::chrono::duration_cast<ms_time>(end - start);
	} while (ms > elapsed.count());
}

Game::Color::~Color()
{
}
