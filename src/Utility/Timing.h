#pragma once

#include "../Core/Object.h"
#include <chrono>

namespace Aegis
{
	class TimingBase : public Object
	{
	public:
		virtual ~TimingBase() = default;

		virtual void Start() = 0;
		virtual void Update() = 0;
		void Stop();

		double GetTimeInSeconds() const;
		double GetTimeInMS() const;

		bool IsPaused() const;
		bool IsStopped() const;

	protected:
		std::chrono::steady_clock::time_point start_time_;
		std::chrono::steady_clock::time_point end_time_;
		double time_in_ms_ = 0.0;

		bool stopped_ = true;
	};

	class Timer : public TimingBase
	{
	public:
		Timer();

		void Start(double time);
		void Update() override;
		void Resume();

	private:
		void Start() override {};
	};

	class StopWatch : public TimingBase
	{
	public:
		void Start() override;
		void Update() override;
		void Restart();
	};
}
