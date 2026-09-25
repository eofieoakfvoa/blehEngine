#pragma once
#include <chrono>
#include <print>
namespace bleh::Benchmark
{
	//https://www.youtube.com/watch?v=YG4jexlSAjc
	class Timer
	{

		public:
			inline Timer()
			{
				_StartTimepoint = std::chrono::high_resolution_clock::now();
			}
			inline ~Timer()
			{
				Stop();
			}
			inline void Stop()
			{
				auto endTimePoints = std::chrono::high_resolution_clock::now();
				auto start = std::chrono::time_point_cast<std::chrono::microseconds>(_StartTimepoint).time_since_epoch().count();
				auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoints).time_since_epoch().count();
				auto duration = end - start;
				double ms = duration * 0.001;
				std::println("Took {} ms", duration, ms);
			}
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> _StartTimepoint;
	};

}