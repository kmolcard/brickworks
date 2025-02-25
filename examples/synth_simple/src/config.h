/*
 * Brickworks
 *
 * Copyright (C) 2022, 2023 Orastron Srl unipersonale
 *
 * Brickworks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Brickworks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Brickworks.  If not, see <http://www.gnu.org/licenses/>.
 *
 * File authors: Stefano D'Angelo
 */

#ifndef _CONFIG_H
#define _CONFIG_H

// Definitions

#define IO_MONO			1
#define IO_STEREO		(1<<1)

struct config_io_bus {
	const char	*name;
	char		 out;
	char		 aux;
	char		 cv;
	char		 configs;
};

struct config_parameter {
	const char	*name;
	const char	*shortName;
	const char	*units;
	char		 out;
	char		 bypass;
	int		 steps;
	float		 defaultValueUnmapped;
};

// Data

#define COMPANY_NAME		"Orastron"
#define COMPANY_WEBSITE		"https://www.orastron.com/"
#define COMPANY_MAILTO		"mailto:info@orastron.com"

#define PLUGIN_NAME		"bw_example_synth_simple"
#define PLUGIN_VERSION		"1.0.0"

#define NUM_BUSES_IN		0
#define NUM_BUSES_OUT		1
#define NUM_CHANNELS_IN		0
#define NUM_CHANNELS_OUT	1

static struct config_io_bus config_buses_out[NUM_BUSES_OUT] = {
	{ "Audio out", 1, 0, 0, IO_MONO }
};

#define NUM_PARAMETERS		11

static struct config_parameter config_parameters[NUM_PARAMETERS] = {
	{ "Volume", "Volume", "", 0, 0, 0, 0.5f },
	{ "Master tune", "Master tune", "st", 0, 0, 0, 0.5f },
	{ "Portamento", "Portamento", "s", 0, 0, 0, 0.f },
	{ "Pulse width", "PW", "%", 0, 0, 0, 0.5f },
	{ "Cutoff", "Cutoff", "Hz", 0, 0, 0, 1.f },
	{ "Q", "Q", "", 0, 0, 0, 0.f },
	{ "Attack", "Attack", "s", 0, 0, 0, 0.f },
	{ "Decay", "Decay", "s", 0, 0, 0, 0.f },
	{ "Sustain", "Sustain", "%", 0, 0, 0, 1.f },
	{ "Release", "Release", "0", 0, 0, 0, 0.f },
	{ "Level", "Level", "", 1, 0, 0, 0.f }
};

// Internal API

#include "bw_example_synth_simple.h"

#define P_TYPE				bw_example_synth_simple
#define P_INIT				bw_example_synth_simple_init
#define P_SET_SAMPLE_RATE		bw_example_synth_simple_set_sample_rate
#define P_RESET				bw_example_synth_simple_reset
#define P_PROCESS			bw_example_synth_simple_process
#define P_SET_PARAMETER			bw_example_synth_simple_set_parameter
#define P_GET_PARAMETER			bw_example_synth_simple_get_parameter
#define P_NOTE_ON			bw_example_synth_simple_note_on
#define P_NOTE_OFF			bw_example_synth_simple_note_off

#endif
