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
 * File author: Stefano D'Angelo
 */

#ifndef _BW_EXAMPLE_FX_COMP_H
#define _BW_EXAMPLE_FX_COMP_H

#include "platform.h"

#include <bw_comp.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	p_thresh,
	p_ratio,
	p_attack,
	p_release,
	p_gain,
	p_n
};

struct _bw_example_fx_comp {
	// Sub-components
	bw_comp_coeffs	comp_coeffs;
	bw_comp_state	comp_state;

	// Parameters
	float		params[p_n];
};
typedef struct _bw_example_fx_comp bw_example_fx_comp;

void bw_example_fx_comp_init(bw_example_fx_comp *instance);
void bw_example_fx_comp_set_sample_rate(bw_example_fx_comp *instance, float sample_rate);
void bw_example_fx_comp_reset(bw_example_fx_comp *instance);
void bw_example_fx_comp_process(bw_example_fx_comp *instance, const float** x, float** y, int n_samples);
void bw_example_fx_comp_set_parameter(bw_example_fx_comp *instance, int index, float value);
float bw_example_fx_comp_get_parameter(bw_example_fx_comp *instance, int index);

#ifdef __cplusplus
}
#endif

#endif
