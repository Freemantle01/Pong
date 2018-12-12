#pragma once
#include <atomic>
#include <mutex>
#include <random>
#include <chrono>
namespace Game
{
	class Color
	{
	public:
		Color();
		~Color();
		int GenerateRandomNumber(const unsigned int& from, const unsigned int& to);
		void ChangeRGB();
		std::atomic<int> r;//red
		std::atomic<int> g;//green
		std::atomic<int> b;//blue
		std::atomic<int> alpha;//opacity
		std::mutex mutex;
	private: 
		void DelayTime(long long ms);
	};
}
