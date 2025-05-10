#include "interacter.hpp"

Interacter::Interacter(long interval_ms)
{
	interact_interval_ms = interval_ms;
	update_interaction_tick();
}

void Interacter::update_interaction_tick()
{
	last_interaction_tick = millis();
}

bool Interacter::can_interact()
{
	return ((long)(millis()) - last_interaction_tick) >= interact_interval_ms;
}

void Interacter::add_cooldown(long cooldown_ms)
{
	update_interaction_tick();
	last_interaction_tick += cooldown_ms;
}
