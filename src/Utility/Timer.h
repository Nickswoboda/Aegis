#pragma once

#include <chrono>

namespace Aegis
{
	class Timer
	{
	public:
		void Start(double duration);
		void Update();
		void Pause();
		void Stop();
		double GetRemainingInSeconds();
		double GetRemainingInMilliseconds();

		std::chrono::steady_clock::time_point start_time_;
		std::chrono::steady_clock::time_point end_time_;
		double time_remaining_ = 0.0;
		bool paused_ = false;
		bool stopped_ = true;

	};
}
