// The author disclaims copyright to this source code.
#ifndef POWERCOLLECTOR_H
#define POWERCOLLECTOR_H

#include "Component.h"
#include "Clock.h"
#include "Log.h"
#include "Thermometer.h"
#include "Wattmeter.h"

class PowerCollector: public Component, public Input, public Output {

public:
	enum State {
		WAITING, MEASURING, LOGGING
	};

	PowerCollector(Clock *clock, Wattmeter* meter, Log* currentLog,
			Log* voltageLog, Log* powerLog, unsigned long measurementIntervalSeconds);
	virtual ~PowerCollector();

	void setup();
	void read();
	void write();

private:

	Clock* clock;
	Wattmeter* meter;
	Log* currentLog;
	Log* voltageLog;
	Log* powerLog;
	State state;
	unsigned long measurementIntervalMillis;
	unsigned long nextMeasurementTimestamp;
};

#endif
