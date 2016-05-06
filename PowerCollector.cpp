// The author disclaims copyright to this source code.
#include <Wire.h>
#include "Debug.h"
#include "PowerCollector.h"

PowerCollector::PowerCollector(Clock *clk, Wattmeter* m, Log* c, Log* v, Log* p, unsigned long measurementIntervalSeconds) {

	clock = clk;
	meter = m;
	currentLog = c;
	voltageLog = v;
	powerLog = p;
	state = WAITING;
	nextMeasurementTimestamp = 0;
	measurementIntervalMillis = measurementIntervalSeconds * 1000;
}

PowerCollector::~PowerCollector() {
}

void PowerCollector::setup() {
	Debug::getInstance()->debug("PowerCollector::setup");
}

void PowerCollector::read() {
	if (state == WAITING) {
		unsigned long now = clock->getTimestamp();
		if (now > nextMeasurementTimestamp) {
			Debug::getInstance()->debug("PowerCollector::read next measurement");
			state = MEASURING;
			meter->startMeasurement();
		}
	} else if (state == MEASURING && meter->isReady()) {
		Debug::getInstance()->debug("TemperatureCollector::read next measurement ready");
		state = LOGGING;
	}
}

void PowerCollector::write() {
	if (state == LOGGING) {
		unsigned long now = clock->getTimestamp();
		nextMeasurementTimestamp = now + measurementIntervalMillis;
		state = WAITING;
		voltageLog->log(String(meter->getBusVoltage(), 2));
		currentLog->log(String(meter->getShuntCurrent(), 2));
		powerLog->log(String(meter->getBusPower(), 2));
	}
}
