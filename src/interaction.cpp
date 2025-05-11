#include "interaction.hpp"

Interaction::Interaction(const long interval_ms)
{
	interact_interval_ms = interval_ms;
	update_interaction_tick();
}

void Interaction::update_interaction_tick()
{
	last_interaction_tick = millis();
}

bool Interaction::can_interact() const
{
	return ((long)(millis()) - last_interaction_tick) >= interact_interval_ms;
}

void Interaction::add_cooldown(const long cooldown_ms)
{
	update_interaction_tick();
	last_interaction_tick += cooldown_ms;
}
