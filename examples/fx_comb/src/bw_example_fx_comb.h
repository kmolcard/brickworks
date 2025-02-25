/*
 * Brickworks
 *
 * Copyright (C) 2023 Orastron Srl unipersonale
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

#ifndef _BW_EXAMPLE_FX_COMB_H
#define _BW_EXAMPLE_FX_COMB_H

#include "platform.h"

#include <bw_comb.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	p_ff_delay,
	p_fb_delay,
	p_blend,
	p_ff,
	p_fb,
	p_n
};

struct _bw_example_fx_comb {
	// Sub-components
	bw_comb_coeffs	 comb_coeffs;
	bw_comb_state	 comb_state;

	// Parameters
	float		 params[p_n];
};
typedef struct _bw_example_fx_comb bw_example_fx_comb;

void bw_example_fx_comb_init(bw_example_fx_comb *instance);
void bw_example_fx_comb_set_sample_rate(bw_example_fx_comb *instance, float sample_rate);
size_t bw_example_fx_comb_mem_req(bw_example_fx_comb *instance);
void bw_example_fx_comb_mem_set(bw_example_fx_comb *instance, void *mem);
void bw_example_fx_comb_reset(bw_example_fx_comb *instance);
void bw_example_fx_comb_process(bw_example_fx_comb *instance, const float** x, float** y, int n_samples);
void bw_example_fx_comb_set_parameter(bw_example_fx_comb *instance, int index, float value);
float bw_example_fx_comb_get_parameter(bw_example_fx_comb *instance, int index);

#ifdef __cplusplus
}
#endif

#endif
