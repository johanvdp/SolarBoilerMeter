// The author disclaims copyright to this source code.
#include "Debug.h"

Debug* Debug::instance = NULL;

Debug* Debug::createInstance(Clock* clk) {
	if (!instance) {
		instance = new Debug(clk);
	}
	return instance;
}

Debug* Debug::getInstance() {
	return instance;
}

Debug::Debug(Clock* clk) {
	clock = clk;
	previousTimestamp = 0;
}

Debug::~Debug() {
}

void Debug::setup() {
	Serial.begin(115200);
	Debug::getInstance()->debug("Debug::setup");
}

void Debug::debug(String debug) {
	if (debugEnabled) {
		Serial.println(timestamps() + ";DEBUG;" + debug);
	}
}

void Debug::info(String info) {
	if (infoEnabled) {
		Serial.println(timestamps() + ";INFO;" + info);
	}
}

void Debug::error(String error) {
	if (errorEnabled) {
		Serial.println(timestamps() + ";ERROR;" + error);
	}
}

const String Debug::zeroTemplate = "00000000000000000000";

String Debug::timestamps() {
	unsigned long now = clock->getTimestamp();
	unsigned long relative = now - previousTimestamp;
	previousTimestamp = now;
	return fixedLength(now) + ";" + fixedLength(relative);
}

String Debug::fixedLength(unsigned long number) {
	String text = String(number);
	String maxed = text.substring(0, 10);
	int padLength = 10 - maxed.length();
	String padding = zeroTemplate.substring(0, padLength);
	String result = padding + maxed;
	return result;
}
