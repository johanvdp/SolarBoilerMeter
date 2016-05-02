// The author disclaims copyright to this source code.
#ifndef LOG_H
#define LOG_H

#include <Arduino.h>
#include "Component.h"

class Log : public Component {

public:
	virtual ~Log() {};
	virtual void log(String value)= 0;
};

class DebugLog : public Log {

public:
	DebugLog(String source);
	virtual ~DebugLog();

	void setup();

	virtual void log(String value);

private:
	String source;
};
#endif
