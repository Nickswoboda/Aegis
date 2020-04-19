#pragma once

#include <chrono>

namespace Aegis
{
	class Timer
	{
	public:
		void Start();
		void Update();
		void Reset();
		void Pause();
		void Stop();
		double GetElapsedInSeconds();
		double GetElapsedInMilliseconds();

		std::chrono::steady_clock::time_point start_time_;
		std::chrono::steady_clock::time_point end_time_;
		double elapsed_time_ = 0.0;
		bool paused_ = false;
		bool stopped_ = true;

	};
}