// The author disclaims copyright to this source code.
#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include "Clock.h"

class Debug {

public:
	static Debug* createInstance(Clock* clock);
	static Debug* getInstance();

	void setup();

	void debug(String info);
	void info(String info);
	void error(String error);

private:
	static Debug* instance;
	static const String zeroTemplate;

	Clock* clock;
	unsigned long previousTimestamp;

	Debug(Clock* clock);
	virtual ~Debug();
	String timestamps();
	String fixedLength(unsigned long number);

	boolean debugEnabled = 1;
	boolean infoEnabled = 1;
	boolean errorEnabled = 1;
};

#endif
