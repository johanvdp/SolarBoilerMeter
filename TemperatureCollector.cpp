// The author disclaims copyright to this source code.
#include <Wire.h>
#include "Debug.h"
#include "TemperatureCollector.h"

TemperatureCollector::TemperatureCollector(Clock *clk, Thermometer* m, Log* l) {

	clock = clk;
	meter = m;
	log = l;
	state = WAITING;
	nextMeasurementTimestamp = 0;
}

TemperatureCollector::~TemperatureCollector() {
}

void TemperatureCollector::setup() {
	Debug::getInstance()->debug("TemperatureCollector::setup");
}

void TemperatureCollector::read() {
	if (state == WAITING) {
		unsigned long now = clock->getTimestamp();
		if (now > nextMeasurementTimestamp) {
			Debug::getInstance()->debug("TemperatureCollector::read next measurement");
			state = MEASURING;
			meter->startMeasurement();
			nextMeasurementTimestamp = now + MEASUREMENT_PERIOD_MILLIS;
		}
	} else if (state == MEASURING && meter->isReady()) {
		Debug::getInstance()->debug("TemperatureCollector::read next measurement ready");
		state = LOGGING;
	}
}

void TemperatureCollector::write() {
	if (state == LOGGING) {
		state = WAITING;
		log->log(String(meter->getTemperatureC(), 2));
	}
}
