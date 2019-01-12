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

#pragma once

// Set the fan timer period.
void set_fan_timer_period(int secs);

// Turn fan on, and let it turn off automatically once the fan timer expires.
void fan_on();

void fan_set_state(bool on);

