#include "Timer.h"

namespace Aegis
{
	//duration in milliseconds
	void Timer::Start(double duration)
	{
		if (stopped_) {
			start_time_ = std::chrono::high_resolution_clock::now();
			stopped_ = false;
		}
		else {
			paused_ = false;
		}
		time_remaining_ = duration;
	}
	void Timer::Update()
	{
		if (!paused_ && !stopped_) {
			end_time_ = std::chrono::high_resolution_clock::now();
			time_remaining_ -= std::chrono::duration<double, std::milli>(end_time_ - start_time_).count();
			start_time_ = end_time_;
		}
		if (time_remaining_ <= 0){
			Stop();
		}
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
	double Timer::GetRemainingInSeconds()
	{
		return time_remaining_ * .001;
	}
	double Timer::GetRemainingInMilliseconds()
	{
		return time_remaining_;
	}
}
