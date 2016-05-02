// The author disclaims copyright to this source code.
#include "Log.h"
#include "Debug.h"

DebugLog::DebugLog(String name) : Log() {
	source = name;
}

DebugLog::~DebugLog() {
}

void DebugLog::setup() {
	Debug::getInstance()->debug("DebugLog::setup");
}

void DebugLog::log(String value) {
	Debug::getInstance()->info("DebugLog::log " + source + "=" + value);
}
