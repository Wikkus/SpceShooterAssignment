#include "timerManager.h"

TimerManager::~TimerManager() {
	for (unsigned int i = 0; i < _timers.size(); i++) {
		RemoveTimer(i);
	}
}

void TimerManager::Update() {
	for (unsigned int i = 0; i < _timers.size(); i++) {
		_timers[i]->Update();
	}
}

void TimerManager::RemoveTimer(unsigned int timerIndex) {
	_timers[timerIndex] = nullptr;
	delete _timers[timerIndex];
	std::swap(_timers[timerIndex], _timers.back());
	_timers.pop_back();
}

Timer* TimerManager::CreateTimer(float timeInSeconds) {
	Timer* timer = new Timer(timeInSeconds);
	_timers.emplace_back(timer);
	return timer;
}
