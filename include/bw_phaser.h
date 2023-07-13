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

/*!
 *  module_type {{{ dsp }}}
 *  version {{{ 0.5.0 }}}
 *  requires {{{
 *    bw_ap1 bw_common bw_config bw_lp1 bw_math bw_one_pole bw_osc_sin
 *    bw_phase_gen
 *  }}}
 *  description {{{
 *    Phaser containing 4 1st-order allpass filters modulated by a sinusoidal
 *    LFO.
 *  }}}
 *  changelog {{{
 *    <ul>
 *      <li>Version <strong>0.5.0</strong>:
 *        <ul>
 *          <li>Added <code>bw_phaser_process_multi()</code>.</li>
 *          <li>Now properly setting allpass cutoff on reset.</li>
 *          <li>Added C++ wrapper.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.4.0</strong>:
 *        <ul>
 *          <li>First release.</li>
 *        </ul>
 *      </li>
 *    </ul>
 *  }}}
 */

#ifndef _BW_PHASER_H
#define _BW_PHASER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bw_common.h>

/*! api {{{
 *    #### bw_phaser_coeffs
 *  ```>>> */
typedef struct _bw_phaser_coeffs bw_phaser_coeffs;
/*! <<<```
 *    Coefficients and related.
 *
 *    #### bw_phaser_state
 *  ```>>> */
typedef struct _bw_phaser_state bw_phaser_state;
/*! <<<```
 *    Internal state and related.
 *
 *    #### bw_phaser_init()
 *  ```>>> */
static inline void bw_phaser_init(bw_phaser_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Initializes input parameter values in `coeffs`.
 *
 *    #### bw_phaser_set_sample_rate()
 *  ```>>> */
static inline void bw_phaser_set_sample_rate(bw_phaser_coeffs *BW_RESTRICT coeffs, float sample_rate);
/*! <<<```
 *    Sets the `sample_rate` (Hz) value in `coeffs`.
 *
 *    #### bw_phaser_reset_coeffs()
 *  ```>>> */
static inline void bw_phaser_reset_coeffs(bw_phaser_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Resets coefficients in `coeffs` to assume their target values.
 *
 *    #### bw_phaser_reset_state()
 *  ```>>> */
static inline void bw_phaser_reset_state(const bw_phaser_coeffs *BW_RESTRICT coeffs, bw_phaser_state *BW_RESTRICT state);
/*! <<<```
 *    Resets the given `state` to its initial values using the given `coeffs`.
 *
 *    #### bw_phaser_update_coeffs_ctrl()
 *  ```>>> */
static inline void bw_phaser_update_coeffs_ctrl(bw_phaser_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Triggers control-rate update of coefficients in `coeffs`.
 *
 *    #### bw_phaser_update_coeffs_audio()
 *  ```>>> */
static inline void bw_phaser_update_coeffs_audio(bw_phaser_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Triggers audio-rate update of coefficients in `coeffs`.
 *
 *    #### bw_phaser_process1()
 *  ```>>> */
static inline float bw_phaser_process1(const bw_phaser_coeffs *BW_RESTRICT coeffs, bw_phaser_state *BW_RESTRICT state, float x);
/*! <<<```
 *    Processes one input sample `x` using `coeffs`, while using and updating
 *    `state`. Returns the corresponding output sample.
 *
 *    #### bw_phaser_process()
 *  ```>>> */
static inline void bw_phaser_process(bw_phaser_coeffs *BW_RESTRICT coeffs, bw_phaser_state *BW_RESTRICT state, const float *x, float *y, int n_samples);
/*! <<<```
 *    Processes the first `n_samples` of the input buffer `x` and fills the
 *    first `n_samples` of the output buffer `y`, while using and updating both
 *    `coeffs` and `state` (control and audio rate).
 *
 *    #### bw_phaser_process_multi()
 *  ```>>> */
static inline void bw_phaser_process_multi(bw_phaser_coeffs *BW_RESTRICT coeffs, bw_phaser_state **BW_RESTRICT state, const float **x, float **y, int n_channels, int n_samples);
/*! <<<```
 *    Processes the first `n_samples` of the `n_channels` input buffers `x` and
 *    fills the first `n_samples` of the `n_channels` output buffers `y`, while
 *    using and updating both the common `coeffs` and each of the `n_channels`
 *    `state`s (control and audio rate).
 *
 *    #### bw_phaser_set_rate()
 *  ```>>> */
static inline void bw_phaser_set_rate(bw_phaser_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the modulation rate `value` (Hz) in `coeffs`.
 *
 *    Default value: `1.f`.
 *
 *    #### bw_phaser_set_center()
 *  ```>>> */
static inline void bw_phaser_set_center(bw_phaser_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the center frequency `value` (Hz) in `coeffs`.
 *
 *    Default value: `1e3f`.
 *
 *    #### bw_phaser_set_amount()
 *  ```>>> */
static inline void bw_phaser_set_amount(bw_phaser_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the modulation amount `value` (octaves) in `coeffs`.
 *
 *    Default value: `1.f`.
 *  }}} */

/*** Implementation ***/

/* WARNING: This part of the file is not part of the public API. Its content may
 * change at any time in future versions. Please, do not use it directly. */

#include <bw_phase_gen.h>
#include <bw_osc_sin.h>
#include <bw_ap1.h>
#include <bw_math.h>

struct _bw_phaser_coeffs {
	// Sub-components
	bw_phase_gen_coeffs	phase_gen_coeffs;
	bw_phase_gen_state	phase_gen_state;
	bw_ap1_coeffs		ap1_coeffs;

	// Coefficients
	float			cutoff_max;

	// Parameters
	float			center;
	float			amount;
};

struct _bw_phaser_state {
	bw_ap1_state		ap1_state[4];
};

static inline void bw_phaser_init(bw_phaser_coeffs *BW_RESTRICT coeffs) {
	bw_phase_gen_init(&coeffs->phase_gen_coeffs);
	bw_ap1_init(&coeffs->ap1_coeffs);
	coeffs->center = 1e3f;
	coeffs->amount = 1.f;
}

static inline void bw_phaser_set_sample_rate(bw_phaser_coeffs *BW_RESTRICT coeffs, float sample_rate) {
	bw_phase_gen_set_sample_rate(&coeffs->phase_gen_coeffs, sample_rate);
	bw_ap1_set_sample_rate(&coeffs->ap1_coeffs, sample_rate);
	coeffs->cutoff_max = 0.48f * sample_rate;
}

static inline void bw_phaser_reset_coeffs(bw_phaser_coeffs *BW_RESTRICT coeffs) {
	bw_phase_gen_reset_coeffs(&coeffs->phase_gen_coeffs);
	bw_phase_gen_reset_state(&coeffs->phase_gen_coeffs, &coeffs->phase_gen_state, 0.f);
	bw_ap1_set_cutoff(&coeffs->ap1_coeffs, bw_clipf(coeffs->center, 1.f, coeffs->cutoff_max));
	bw_ap1_reset_coeffs(&coeffs->ap1_coeffs);
}

static inline void bw_phaser_reset_state(const bw_phaser_coeffs *BW_RESTRICT coeffs, bw_phaser_state *BW_RESTRICT state) {
	bw_ap1_reset_state(&coeffs->ap1_coeffs, &state->ap1_state[0], 0.f);
	bw_ap1_reset_state(&coeffs->ap1_coeffs, &state->ap1_state[1], 0.f);
	bw_ap1_reset_state(&coeffs->ap1_coeffs, &state->ap1_state[2], 0.f);
	bw_ap1_reset_state(&coeffs->ap1_coeffs, &state->ap1_state[3], 0.f);
}

static inline void bw_phaser_update_coeffs_ctrl(bw_phaser_coeffs *BW_RESTRICT coeffs) {
	bw_phase_gen_update_coeffs_ctrl(&coeffs->phase_gen_coeffs);
}

static inline void bw_phaser_update_coeffs_audio(bw_phaser_coeffs *BW_RESTRICT coeffs) {
	bw_phase_gen_update_coeffs_audio(&coeffs->phase_gen_coeffs);
	float p, pi;
	bw_phase_gen_process1(&coeffs->phase_gen_coeffs, &coeffs->phase_gen_state, &p, &pi);
	const float m = coeffs->amount * bw_osc_sin_process1(p);
	bw_ap1_set_cutoff(&coeffs->ap1_coeffs, bw_clipf(coeffs->center * bw_pow2f_3(m), 1.f, coeffs->cutoff_max));
	bw_ap1_update_coeffs_ctrl(&coeffs->ap1_coeffs);
	bw_ap1_update_coeffs_audio(&coeffs->ap1_coeffs);
}

static inline float bw_phaser_process1(const bw_phaser_coeffs *BW_RESTRICT coeffs, bw_phaser_state *BW_RESTRICT state, float x) {
	float y = bw_ap1_process1(&coeffs->ap1_coeffs, &state->ap1_state[0], x);
	y = bw_ap1_process1(&coeffs->ap1_coeffs, &state->ap1_state[1], y);
	y = bw_ap1_process1(&coeffs->ap1_coeffs, &state->ap1_state[2], y);
	return x + bw_ap1_process1(&coeffs->ap1_coeffs, &state->ap1_state[3], y);
}

static inline void bw_phaser_process(bw_phaser_coeffs *BW_RESTRICT coeffs, bw_phaser_state *BW_RESTRICT state, const float *x, float *y, int n_samples) {
	bw_phaser_update_coeffs_ctrl(coeffs);
	for (int i = 0; i < n_samples; i++) {
		bw_phaser_update_coeffs_audio(coeffs);
		y[i] = bw_phaser_process1(coeffs, state, x[i]);
	}
}

static inline void bw_phaser_process_multi(bw_phaser_coeffs *BW_RESTRICT coeffs, bw_phaser_state **BW_RESTRICT state, const float **x, float **y, int n_channels, int n_samples) {
	bw_phaser_update_coeffs_ctrl(coeffs);
	for (int i = 0; i < n_samples; i++) {
		bw_phaser_update_coeffs_audio(coeffs);
		for (int j = 0; j < n_channels; j++)
			y[j][i] = bw_phaser_process1(coeffs, state[j], x[j][i]);
	}
}

static inline void bw_phaser_set_rate(bw_phaser_coeffs *BW_RESTRICT coeffs, float value) {
	bw_phase_gen_set_frequency(&coeffs->phase_gen_coeffs, value);
}

static inline void bw_phaser_set_center(bw_phaser_coeffs *BW_RESTRICT coeffs, float value) {
	coeffs->center = value;
}

static inline void bw_phaser_set_amount(bw_phaser_coeffs *BW_RESTRICT coeffs, float value) {
	coeffs->amount = value;
}

#ifdef __cplusplus
}
#endif

#endif
