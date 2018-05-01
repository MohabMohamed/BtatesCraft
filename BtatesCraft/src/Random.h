#pragma once

#include <random>
#include <chrono>
#include <type_traits>



template<typename REngine = std::mt19937>
class Random
{
private:
	REngine m_randomEngine;
public:
	Random(unsigned long long n = std::chrono::system_clock::now().time_since_epoch().count())
	{
		m_randomEngine.seed(n);
	}

	template<typename T>
	T intInRange(T low, T high)
	{
		static_assert(std::is_integral<T>::value, "Not integral type!");
		std::uniform_int_distribution<T> dist(low, high);
		return dist(m_randomEngine);
	}

	void setSeed(int seed)
	{
		m_randomEngine.seed(seed);
	}

};