#pragma once
#ifndef __AUXTIMER_H__
#define __AUXTIMER_H__

#include "Defs.h"

class AuxTimer
{
public:

	// Constructor
	AuxTimer();

	void Start();
	double ReadMs() const;
	uint64 ReadTicks() const;

private:
	uint64 startTime;
	static uint64 frequency;
};

#endif //__PERFTIMER_H__