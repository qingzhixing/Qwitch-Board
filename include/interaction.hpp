#pragma once
#ifndef INTERACTION_H_
#define INTERACTION_H_

#include <Arduino.h>

class Interaction
{
private:
	long last_interaction_tick{};
	long interact_interval_ms;

public:
	explicit Interaction(const long interval_ms);
	void update_interaction_tick();
	bool can_interact() const;
	void add_cooldown(const long cooldown_ms);
};

#endif //! INTERACTION_H_