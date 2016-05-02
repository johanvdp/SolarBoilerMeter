// The author disclaims copyright to this source code.

#include "Thermometer.h"

#include <HardwareSerial.h>
#include <OneWire.h>
#include <pins_arduino.h>

#include "Debug.h"

Thermometer::Thermometer(Clock *clk) {
	clock = clk;
	state = DISCONNECTED;
	readyTimestamp = 0;
	temperatureC = 0.0;
	ds = new OneWire(D2);
}

Thermometer::~Thermometer() {
}

void Thermometer::setup() {
	Debug::getInstance()->debug("Thermometer::setup");
	startMeasurement();
}

void Thermometer::read() {
	if (state == WAIT_FOR_RESULT) {
		unsigned long now = clock->getTimestamp();
		if (now > readyTimestamp) {
			Debug::getInstance()->info("Thermometer::read conversion ready");
			uint8_t present = ds->reset();
			if (present == 0) {
				Debug::getInstance()->error(
						"Thermometer::read connection lost (no device present)");
				state = DISCONNECTED;
				return;
			}
			ds->select(addr);
			ds->write(0xBE);
			// read scratch pad (9 bytes)
			for (int i = 0; i < 9; i++) {
				data[i] = ds->read();
			}
			// 1st 8 are data, last one is CRC
			if (OneWire::crc8(data, 8) != data[8]) {
				Debug::getInstance()->error(
						"Thermometer::read connection lost (invalid data CRC)");
				state = DISCONNECTED;
				return;
			}
			// fixed device type is 0x28=DS18B20
			if (addr[0] != 0x28) {
				Debug::getInstance()->error(
						"Thermometer::read connection lost (not a DS18B20)");
				state = DISCONNECTED;
				return;
			}
			int16_t raw = (data[1] << 8) | data[0];
			temperatureC = (float) raw / 16.0;
			Debug::getInstance()->debug(
					"Thermometer::read temperature " + String(temperatureC, 2));
			state = IDLE;
		}
	} else if (state == DISCONNECTED) {
		// try connect
		// Debug::getInstance()->debug("Thermometer::read try connect");
		if (!ds->search(addr)) {
			// failed, prepare for next try
			// Debug::getInstance()->debug("Thermometer::read still disconnected (no device found)");
			ds->reset_search();
			return;
		} else {
			if (OneWire::crc8(addr, 7) != addr[7]) {
				Debug::getInstance()->debug(
						"Thermometer::read still disconnected (invalid device CRC)");
				return;
			}
			Debug::getInstance()->info("Thermometer::read connected");
			state = IDLE;
		}
	}
}

void Thermometer::startMeasurement() {
	if (state == IDLE) {
		Debug::getInstance()->debug(
				"Thermometer::startMeasurement start requested");
		state = START_REQUESTED;
	} else {
		Debug::getInstance()->error(
				"Thermometer::startMeasurement failed not idle");
	}
}

double Thermometer::getTemperatureC() {
	return temperatureC;
}

boolean Thermometer::isReady() {
	return state == IDLE;
}

void Thermometer::write() {
	if (state == START_REQUESTED) {
		Debug::getInstance()->debug("Thermometer::write start requested");
		uint8_t present = ds->reset();
		if (present == 0) {
			Debug::getInstance()->error(
					"Thermometer::write connection lost (no device present)");
			state = DISCONNECTED;
			return;
		}
		// start conversion
		ds->select(addr);
		ds->write(0x44, 1);

		unsigned long now = clock->getTimestamp();
		readyTimestamp = now + CONVERSION_TIME_MILLIS;
		state = WAIT_FOR_RESULT;
	}
}

