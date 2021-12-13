
#include "AuxTImer.h"
#include "SDL\include\SDL_timer.h"

uint64 AuxTimer::frequency = 0;

// L07: DONE 2: Fill Constructor, Start(),ReadMs() and ReadTicks() methods
// they are simple, one line each!

AuxTimer::AuxTimer()
{
	if (frequency == 0) frequency = SDL_GetPerformanceFrequency();

	Start();
}

void AuxTimer::Start()
{
	startTime = SDL_GetPerformanceCounter();
}

double AuxTimer::ReadMs() const
{
	return 1000.0 * (double(SDL_GetPerformanceCounter() - startTime) / double(frequency));
}

uint64 AuxTimer::ReadTicks() const
{
	return SDL_GetPerformanceCounter() - startTime;
}
