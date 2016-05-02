// The author disclaims copyright to this source code.
#ifndef TEMPERATURECOLLECTOR_H
#define TEMPERATURECOLLECTOR_H

#include "Component.h"
#include "Clock.h"
#include "Log.h"
#include "Thermometer.h"
#include "Wattmeter.h"

class TemperatureCollector: public Component, public Input, public Output {

public:
	enum State {
		WAITING, MEASURING, LOGGING
	};

	TemperatureCollector(Clock *clock, Thermometer* meter, Log* log);
	virtual ~TemperatureCollector();

	void setup();
	void read();
	void write();

private:

	static const int MEASUREMENT_PERIOD_MILLIS = 60000;

	Clock* clock;
	Thermometer* meter;
	Log* log;
	State state;
	unsigned long nextMeasurementTimestamp;
};

#endif
