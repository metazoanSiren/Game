#include "Timer.h"



void Timer::Start() {
	prevTicks = SDL_GetTicks();
	currentTicks = SDL_GetTicks();

}
void Timer::UpdateFrameTicks() {
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();
}
float Timer::GetDeltaTime() const {

	return static_cast<float>((currentTicks - prevTicks) / 1000.0f);

}
unsigned int Timer::GetSleepTime(const unsigned int fps_) {
	unsigned int milliPreFrame = 1000 / fps_;
	if (milliPreFrame == 0) {
		return 0;

	}
	unsigned int sleepTime = milliPreFrame - SDL_GetTicks();
	if (sleepTime > milliPreFrame)
		return milliPreFrame;
	else
	{
		return sleepTime;
	}
		
}
float Timer::GetCurrentTicks() const {
	return static_cast<float>(currentTicks);

}


Timer::Timer() : prevTicks(0), currentTicks(0){

}


Timer::~Timer(){

}
