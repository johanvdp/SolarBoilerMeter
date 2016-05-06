// The author disclaims copyright to this source code.
#include "ThingSpeakLog.h"
#include <WiFiClient.h>
#include "Debug.h"

ThingSpeakLog::ThingSpeakLog(String field, String writeKey) : Log() {
	this->field = field;
	this->writeKey = writeKey;
}

ThingSpeakLog::~ThingSpeakLog() {
}

void ThingSpeakLog::setup() {
	Debug::getInstance()->debug("ThingSpeakLog::setup");
}

/**
 * Send update to ThingSpeak channel field1 (using a HTTP GET request).
 * GET https://api.thingspeak.com/update?api_key=WRITE_KEY&field1=VALUE
 */
void ThingSpeakLog::log(String value) {
	Debug::getInstance()->info("ThingSpeakLog::log " + field + "=" + value);

	WiFiClient client;
	if (!client.connect(thingSpeakHost, thingSpeakPort)) {
		Debug::getInstance()->error("ThingSpeakLog::log connect failed");
		return;
	}

	// create the request
	String request = String("GET /update?api_key=") + writeKey + "&" + field + "=" + value + " HTTP/1.1\r\n" + "Host: " + thingSpeakHost + "\r\n"
			+ "Connection: close\r\n\r\n";
	Debug::getInstance()->debug("ThingSpeakLog::log request " + request);

	// send the request
	client.print(request);
	unsigned long now = millis();
	unsigned long timeout = now + 5000;
	while (client.available() == 0) {
		if (millis() > timeout) {
			Debug::getInstance()->error("ThingSpeakLog::log request timeout");
			client.stop();
			return;
		}
	}

	// read response
	bool httpResult = false;
	while (client.available()) {
		String line = client.readStringUntil('\r');
		if (!httpResult) {
			httpResult = true;
			Debug::getInstance()->info("ThingSpeakLog::log response " + line);
		} else {
			//Debug::getInstance()->debug("ThingSpeakLog::log response " + line);
		}
	}
	client.stop();
	Debug::getInstance()->debug("ThingSpeakLog::log end");
}
