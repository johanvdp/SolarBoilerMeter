// The author disclaims copyright to this source code.
#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <Arduino.h>
#include <OneWire.h>
#include "Component.h"
#include "Clock.h"

class Thermometer: public Component, public Input, public Output {

public:
	enum State {
		DISCONNECTED, IDLE, START_REQUESTED, WAIT_FOR_RESULT
	};

	Thermometer(Clock *clock);
	virtual ~Thermometer();

	void setup();
	void read();
	void write();

	void startMeasurement();
	boolean isReady();
	double getTemperatureC();

private:
	static const int MEASUREMENT_PERIOD_MILLIS = 60000;
	static const int CONVERSION_TIME_MILLIS = 1000;

	OneWire* ds;
	byte addr[8];
	byte data[12];
	Clock* clock;
	State state;
	unsigned long readyTimestamp;
	double temperatureC;
};

#endif
