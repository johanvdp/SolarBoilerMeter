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

// The following secrets are defined in an file external to the repository.
// The secret file contains the following lines:
//
// // ==============================
// // DO NOT PLACE IN REPOSITORY
// // ==============================
// // WiFi access point credentials
// // const char* wifiSSID = "??????";
// // const char* wifiPassword = "??????";
// // ------------------------------
// // ThingSpeak channel credentials
// const char* thingSpeakWriteAPIKey_Temperature = "??????";
// const char* thingSpeakWriteAPIKey_Power = "??????";
// // ==============================

// WiFi access point credentials
extern const char* wifiSSID;
extern const char* wifiPassword;
// ThingSpeak channel credentials
extern const char* thingSpeakWriteAPIKey_Temperature;
extern const char* thingSpeakWriteAPIKey_Power;

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
	Log* powersupplyWattLog;
	Log* temperatureDegCLog;
	PowerCollector* powerCollector;
	TemperatureCollector* temperatureCollector;
};

#endif
