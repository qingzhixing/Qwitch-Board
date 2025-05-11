#include "interaction.hpp"

Interaction::Interaction(const long interval_ms)
{
	interact_interval_ms = interval_ms;
	update_interaction_tick();
}

void Interaction::update_interaction_tick()
{
	last_interaction_tick = static_cast<long>(millis());
}

bool Interaction::can_interact() const
{
	return (static_cast<long>(millis()) - last_interaction_tick) >= interact_interval_ms;
}

void Interaction::add_cooldown(const long cooldown_ms)
{
	update_interaction_tick();
	last_interaction_tick += cooldown_ms;
}
