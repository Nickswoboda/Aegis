#include "Timing.h"

namespace Aegis
{
	double TimingBase::GetTimeInSeconds() const 
	{
		return time_in_ms_ * .001;
	}

	double TimingBase::GetTimeInMS() const
	{
		return time_in_ms_;
	}

	void TimingBase::Stop()
	{
		stopped_ = true;
	}

	bool TimingBase::IsStopped() const
	{
		return stopped_;
	}

	Timer::Timer()
	{
		AddSignal("done");
	}
	//duration in milliseconds
	void Timer::Start(double duration)
	{
		time_in_ms_ = duration;
		start_time_ = std::chrono::high_resolution_clock::now();
		stopped_ = false;
	}

	void Timer::Resume()
	{
		Start(time_in_ms_);
	}

	void Timer::Update()
	{
		if (!stopped_) {
			end_time_ = std::chrono::high_resolution_clock::now();
			time_in_ms_ -= std::chrono::duration<double, std::milli>(end_time_ - start_time_).count();
			start_time_ = end_time_;

			if (time_in_ms_ <= 0){
				Emit("done");
				Stop();
			}
		}
	}

	void StopWatch::Start()
	{
		start_time_ = std::chrono::high_resolution_clock::now();
		stopped_ = false;
	}

	void StopWatch::Update()
	{
		if (!stopped_) {
			end_time_ = std::chrono::high_resolution_clock::now();
			time_in_ms_ += std::chrono::duration<double, std::milli>(end_time_ - start_time_).count();
			start_time_ = end_time_;
		}
	}

	void StopWatch::Restart()
	{
		time_in_ms_ = 0.0;
		Start();
	}
}
