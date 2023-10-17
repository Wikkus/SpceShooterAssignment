#pragma once
#include "timer.h"

#include <vector>

class TimerManager {
public:
	TimerManager() {}
	~TimerManager();

	void Update();
	
	void RemoveTimer(unsigned int timerIndex);

	Timer* CreateTimer(float timeInSeconds);

private:
	std::vector<Timer*> _timers;
};