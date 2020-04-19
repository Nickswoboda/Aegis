#include "Timer.h"

namespace Aegis
{
	void Timer::Start()
	{
		if (stopped_) {
			start_time_ = std::chrono::high_resolution_clock::now();
			stopped_ = false;
		}
		else {
			paused_ = false;
		}
	}
	void Timer::Update()
	{
		if (!paused_ && !stopped_) {
			end_time_ = std::chrono::high_resolution_clock::now();
			elapsed_time_ = std::chrono::duration<double, std::milli>(end_time_ - start_time_).count();
		}
	}
	void Timer::Reset()
	{
		start_time_ = end_time_;
		elapsed_time_ = 0.0;
	}
	void Timer::Pause()
	{
		if (!stopped_) {
			paused_ = true;
		}
	}
	void Timer::Stop()
	{
		stopped_ = true;
		paused_ = false;
	}
	double Timer::GetElapsedInSeconds()
	{
		return elapsed_time_ * .001;
	}
	double Timer::GetElapsedInMilliseconds()
	{
		return elapsed_time_;
	}
}
