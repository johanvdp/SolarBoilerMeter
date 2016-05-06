// The author disclaims copyright to this source code.
#ifndef WIFICOMPONENT_H
#define WIFICOMPONENT_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "Component.h"

/**
 * The server handles client requests on every loop.
 */
class WiFiComponent: public Component, public Process {
public:

	WiFiComponent(const char* ssid, const char* password);
	virtual ~WiFiComponent();

	void setup();
	void process();

	bool isReady();

	static bool ready;
private:

	static void onEvent(WiFiEvent_t event);

	const char* ap_id;
	const char* ap_password;
	wl_status_t previousStatus = WL_IDLE_STATUS;
};

#endif
