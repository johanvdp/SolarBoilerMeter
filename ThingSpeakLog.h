// The author disclaims copyright to this source code.
#ifndef THINGSPEAKLOG_H
#define THINGSPEAKLOG_H

#include <Arduino.h>
#include "Log.h"

class ThingSpeakLog : public Log {

public:
	ThingSpeakLog(String field, String writeKey);
	virtual ~ThingSpeakLog();
	void setup();
	void log(String value);

private:
	const char* thingSpeakHost = "api.thingspeak.com";
	const int thingSpeakPort = 80;

	String field;
	String writeKey;
};

#endif
