#include "timer.h"

#include "gameEngine.h"

Timer::Timer(float timeInSeconds) : _timeInSeconds(timeInSeconds) {
	_currentTime = 0.f;
}

Timer::~Timer() {}

const bool Timer::GetTimerFinished() const {
	return _timerFinished;
}

void Timer::ResetTimer() {
	_currentTime = _timeInSeconds;
	_timerFinished = false;
}

void Timer::Update() {
	if (!_timerFinished) {
		if (_currentTime > 0) {
			_currentTime -= deltaTime;
		} else {
			_timerFinished = true;
		}
	}
}

