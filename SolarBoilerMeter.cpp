// The author disclaims copyright to this source code.

#include "SolarBoilerMeter.h"

#include <Wire.h>

#include "Clock.h"
#include "Debug.h"
#include "Log.h"
#include "PowerCollector.h"
#include "TemperatureCollector.h"
#include "Thermometer.h"
#include "Wattmeter.h"
#include "WiFiComponent.h"

/**
 * Construct the application by constructing all its components.
 */
SolarBoilerMeter::SolarBoilerMeter() {

	clock = new Clock();
	debug = Debug::createInstance(clock);
	wifi = new WiFiComponent(ssid, password);
	wattmeter = new Wattmeter(clock);
	thermometer = new Thermometer(clock);
	powersupplyAmpLog = new DebugLog("powersupplyAmp");
	powersupplyVoltLog = new DebugLog("powersupplyVolt");
	temperatureDegCLog = new DebugLog("temperatureDegC");
	powerCollector = new PowerCollector(clock, wattmeter, powersupplyAmpLog,
			powersupplyVoltLog);
	temperatureCollector = new TemperatureCollector(clock, thermometer,
			temperatureDegCLog);
}

SolarBoilerMeter::~SolarBoilerMeter() {

}

/**
 * Called once to setup the application.
 *
 * Will initialize (setup) all external libraries and components that make up the application.
 */
void SolarBoilerMeter::setup() {
	Debug::getInstance()->debug("SolarBoilerMeter::setup");

	// I2C wire protocol for power meter component
	Wire.begin(SDA, SCL);

	// external library
	//..

	// all components
	debug->setup();
	clock->setup();
	wifi->setup();
	wattmeter->setup();
	thermometer->setup();
	powersupplyAmpLog->setup();
	powersupplyVoltLog->setup();
	temperatureDegCLog->setup();
	powerCollector->setup();
	temperatureCollector->setup();
}

/**
 * Called continuously to keep the application going.
 *
 * The application must execute and return quickly.
 * If not, the ESP Arduino implementation can not perform its housekeeping tasks and the built-in watchdog timer will reset the chip/application.
 *
 * The components that make up the application are triggered to perform their respective Input, Process, and Output operations (in that order).
 */
void SolarBoilerMeter::loop() {

	// read all inputs
	clock->read();
	wattmeter->read();
	thermometer->read();
	powerCollector->read();
	temperatureCollector->read();

	// perform processing
	wifi->process();

	// write all outputs
	wattmeter->write();
	thermometer->write();
	powerCollector->write();
	temperatureCollector->write();
}

/**
 * The singleton instance of the SolarBoilerMeter application.
 */
SolarBoilerMeter instance;

/**
 * Arduino setup entry point.
 * Forwards the call into the application instance.
 */
void setup() {
	instance.setup();
}

/**
 * Arduino loop entry point.
 * Forwards the call into the application instance.
 */
void loop() {
	instance.loop();
}
