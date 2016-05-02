// The author disclaims copyright to this source code.
#include <Wire.h>
#include "Debug.h"
#include "PowerCollector.h"

PowerCollector::PowerCollector(Clock *clk, Wattmeter* m, Log* c, Log* v) {

	clock = clk;
	meter = m;
	currentLog = c;
	voltageLog = v;
	state = WAITING;
	nextMeasurementTimestamp = 0;
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
			state = MEASURING;
			meter->startMeasurement();
			nextMeasurementTimestamp = now + MEASUREMENT_PERIOD_MILLIS;
		}
	} else if (state == MEASURING && meter->isReady()) {
		state = LOGGING;
	}
}

void PowerCollector::write() {
	if (state == LOGGING) {
		state = WAITING;
		voltageLog->log(String(meter->getBusVoltage(), 2));
		currentLog->log(String(meter->getShuntCurrent(), 2));
	}
}
