// The author disclaims copyright to this source code.
#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#include <Arduino.h>
#include "Log.h"

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
