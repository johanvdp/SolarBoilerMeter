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
			Log* voltageLog);
	virtual ~PowerCollector();

	void setup();
	void read();
	void write();

private:

	static const int MEASUREMENT_PERIOD_MILLIS = 60000;

	Clock* clock;
	Wattmeter* meter;
	Log* currentLog;
	Log* voltageLog;
	State state;
	unsigned long nextMeasurementTimestamp;
};

#endif
