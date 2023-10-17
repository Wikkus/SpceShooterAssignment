#pragma once

class Timer {
public:
	Timer(float timeInSeconds);
	~Timer();

	const bool GetTimerFinished() const;

	void ResetTimer();
	void Update();

private:
	bool _timerFinished = false;

	const float _timeInSeconds;	
	float _currentTime;

};