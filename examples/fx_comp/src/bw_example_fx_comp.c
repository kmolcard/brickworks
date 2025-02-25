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

#include "bw_example_fx_comp.h"

void bw_example_fx_comp_init(bw_example_fx_comp *instance) {
	bw_comp_init(&instance->comp_coeffs);
}

void bw_example_fx_comp_set_sample_rate(bw_example_fx_comp *instance, float sample_rate) {
	bw_comp_set_sample_rate(&instance->comp_coeffs, sample_rate);
}

void bw_example_fx_comp_reset(bw_example_fx_comp *instance) {
	bw_comp_reset_coeffs(&instance->comp_coeffs);
	bw_comp_reset_state(&instance->comp_coeffs, &instance->comp_state, 0.f, 0.f);
}

void bw_example_fx_comp_process(bw_example_fx_comp *instance, const float** x, float** y, int n_samples) {
	bw_comp_process(&instance->comp_coeffs, &instance->comp_state, x[0], x[0], y[0], n_samples);
}

void bw_example_fx_comp_set_parameter(bw_example_fx_comp *instance, int index, float value) {
	instance->params[index] = value;
	switch (index) {
	case p_thresh:
		bw_comp_set_thresh_dBFS(&instance->comp_coeffs, 60.f * value - 60.f);
		break;
	case p_ratio:
		bw_comp_set_ratio(&instance->comp_coeffs, value);
		break;
	case p_attack:
		bw_comp_set_attack_tau(&instance->comp_coeffs, value);
		break;
	case p_release:
		bw_comp_set_release_tau(&instance->comp_coeffs, value);
		break;
	case p_gain:
		bw_comp_set_gain_dB(&instance->comp_coeffs, 60.f * value);
		break;
	}
}

float bw_example_fx_comp_get_parameter(bw_example_fx_comp *instance, int index) {
	return instance->params[index];
}
