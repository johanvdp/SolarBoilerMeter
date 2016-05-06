// The author disclaims copyright to this source code.

#include "WiFiComponent.h"

#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiType.h>
#include <IPAddress.h>
#include <WiFiClient.h>
#include <Arduino.h>
#include "Debug.h"

bool WiFiComponent::ready = false;

WiFiComponent::WiFiComponent(const char* ssid, const char* password) {
	ap_id = ssid;
	ap_password = password;
}

WiFiComponent::~WiFiComponent() {
}

void WiFiComponent::setup() {
	Debug::getInstance()->debug("WiFiComponent::setup");
	WiFi.disconnect(true);
	delay(1000);

	//callback from C to C++ needs static function
	WiFi.onEvent(reinterpret_cast<WiFiEventCb>(WiFiComponent::onEvent));

	WiFi.begin(ap_id, ap_password);
}

void WiFiComponent::process(void) {
}

void WiFiComponent::onEvent(WiFiEvent_t event) {
	WiFiComponent::ready = false;
	switch (event) {
	case WIFI_EVENT_STAMODE_CONNECTED:
		Debug::getInstance()->info(
				"WiFiComponent::onEvent WIFI_EVENT_STAMODE_CONNECTED");
		break;
	case WIFI_EVENT_STAMODE_DISCONNECTED:
		Debug::getInstance()->info(
				"WiFiComponent::onEvent WIFI_EVENT_STAMODE_DISCONNECTED");
		break;
	case WIFI_EVENT_STAMODE_AUTHMODE_CHANGE:
		Debug::getInstance()->info(
				"WiFiComponent::onEvent WIFI_EVENT_STAMODE_AUTHMODE_CHANGE");
		break;
	case WIFI_EVENT_STAMODE_GOT_IP:
		Debug::getInstance()->info(
				"WiFiComponent::onEvent WIFI_EVENT_STAMODE_GOT_IP: "
						+ WiFi.localIP().toString());
		WiFiComponent::ready = true;
		break;
	case WIFI_EVENT_STAMODE_DHCP_TIMEOUT:
		Debug::getInstance()->info(
				"WiFiComponent::onEvent WIFI_EVENT_STAMODE_DHCP_TIMEOUT");
		break;
	case WIFI_EVENT_SOFTAPMODE_STACONNECTED:
		Debug::getInstance()->info(
				"WiFiComponent::onEvent WIFI_EVENT_SOFTAPMODE_STACONNECTED");
		break;
	case WIFI_EVENT_SOFTAPMODE_STADISCONNECTED:
		Debug::getInstance()->info(
				"WiFiComponent::onEvent WIFI_EVENT_SOFTAPMODE_STADISCONNECTED");
		break;
	case WIFI_EVENT_SOFTAPMODE_PROBEREQRECVED:
		Debug::getInstance()->info(
				"WiFiComponent::onEvent WIFI_EVENT_SOFTAPMODE_PROBEREQRECVED");
		break;
	default:
		Debug::getInstance()->error(
				"WiFiComponent::onEvent UNKNOWN EVENT: " + String(event));
		break;
	}
	if (WiFiComponent::ready) {
		Debug::getInstance()->info("WiFiComponent::onEvent ready");
	} else {
		Debug::getInstance()->info("WiFiComponent::onEvent not ready");
	}
}

bool WiFiComponent::isReady() {
	return WiFiComponent::ready;
}

