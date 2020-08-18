#pragma once
#include <ctime>

class Timer {

public:
	Timer() {
		this->lastLoopTime = getTime();
	}

	double getTime() {
		return clock();
	}

	float getElapsedTime() {
		double time = getTime();
		float elapsedTime = (float)(time - lastLoopTime);
		lastLoopTime = time;
		return elapsedTime;
	}

	double getLastLoopTime() {
		return lastLoopTime;
	}

private:
	double lastLoopTime;

};