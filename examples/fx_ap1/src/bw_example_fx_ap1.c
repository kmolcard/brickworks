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

#include "bw_example_fx_ap1.h"

void bw_example_fx_ap1_init(bw_example_fx_ap1 *instance) {
	bw_ap1_init(&instance->ap1_coeffs);
}

void bw_example_fx_ap1_set_sample_rate(bw_example_fx_ap1 *instance, float sample_rate) {
	bw_ap1_set_sample_rate(&instance->ap1_coeffs, sample_rate);
}

void bw_example_fx_ap1_reset(bw_example_fx_ap1 *instance) {
	bw_ap1_reset_coeffs(&instance->ap1_coeffs);
	bw_ap1_reset_state(&instance->ap1_coeffs, &instance->ap1_state, 0.f);
}

void bw_example_fx_ap1_process(bw_example_fx_ap1 *instance, const float** x, float** y, int n_samples) {
	bw_ap1_process(&instance->ap1_coeffs, &instance->ap1_state, x[0], y[0], n_samples);
}

void bw_example_fx_ap1_set_parameter(bw_example_fx_ap1 *instance, int index, float value) {
	instance->params[index] = value;
	bw_ap1_set_cutoff(&instance->ap1_coeffs, 20.f + (20e3f - 20.f) * value * value * value);
}

float bw_example_fx_ap1_get_parameter(bw_example_fx_ap1 *instance, int index) {
	return instance->params[index];
}
