// The author disclaims copyright to this source code.
#ifndef SOLARBOILERMETER_H
#define SOLARBOILERMETER_H

#include <Arduino.h>
#include "Clock.h"
#include "Debug.h"
#include "Log.h"
#include "PowerCollector.h"
#include "TemperatureCollector.h"
#include "Thermometer.h"
#include "Wattmeter.h"
#include "WiFiComponent.h"

// The following secret is defined in a file external to the repository.
// The secret file contains the following two lines:
// const char* ssid = "station_name";
// const char* password = "station_password";
extern const char* ssid;
extern const char* password;

class SolarBoilerMeter {

public:

	SolarBoilerMeter();
	virtual ~SolarBoilerMeter();

	void setup();
	void loop();

private:
	// I2C wires
	const static uint8_t SDA = D3;
	const static uint8_t SCL = D4;

	Clock* clock;
	Debug* debug;
	WiFiComponent* wifi;
	Wattmeter* wattmeter;
	Thermometer* thermometer;
	Log* powersupplyAmpLog;
	Log* powersupplyVoltLog;
	Log* temperatureDegCLog;
	PowerCollector* powerCollector;
	TemperatureCollector* temperatureCollector;
};

#endif
