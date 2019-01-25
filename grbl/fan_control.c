/*
  fan_control.h - fan control methods
  Part of Grbl

  Copyright (c) 2019 Torsten Martinsen

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "grbl.h"

// get_time() wraps around too early, so use an auxiliary counter
static const int fan_on_chunk = 10; // seconds

static int fan_periods = 1;
static int fan_periods_left = 0;

void set_fan_on_time(int secs)
{
    // Round up.
    fan_periods = (secs + fan_on_chunk - 1)/fan_on_chunk;
}

static uint32_t fan_on_at = 0;

void fan_on()
{
    fan_set_state(true);
    fan_reset_timer();
}

void fan_reset_timer()
{
    fan_on_at = get_time();
    fan_periods_left = fan_periods;
}

void update_fan()
{
    const auto cycles = uint64_t(SystemCoreClock) * fan_on_chunk;
    if (get_time() - fan_on_at < cycles)
        return;
    // Ten seconds have passed
    --fan_periods_left;
    fan_on_at = get_time();
    if (fan_periods_left > 0)
        return;
    fan_set_state(false);
}

void fan_set_state(bool on)
{
    if (on)
        FAN_PORT |= (1 << FAN_BIT);
    else
        FAN_PORT &= ~(1 << FAN_BIT);
}
