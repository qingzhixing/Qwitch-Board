#pragma once
#ifndef _INTERACTER_H_
#define _INTERACTER_H_

#include <Arduino.h>

class Interacter
{
private:
	long last_interaction_tick;
	long interact_interval_ms;

public:
	Interacter(long interval_ms);
	void update_interaction_tick();
	bool can_interact();
	void add_cooldown(long cooldown_ms);
};

#endif //! _INTERACTER_H_