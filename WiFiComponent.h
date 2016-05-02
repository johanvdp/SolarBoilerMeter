// The author disclaims copyright to this source code.
#ifndef WIFICOMPONENT_H
#define WIFICOMPONENT_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

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

private:

	static void onEvent(WiFiEvent_t event);
	void sendMainpage();
	void sendGraph();
	void sendNotFound();

	ESP8266WebServer* server;
	const char* ap_id;
	const char* ap_password;
	wl_status_t previousStatus = WL_IDLE_STATUS;
};

#endif
