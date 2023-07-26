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

/*!
 *  module_type {{{ dsp }}}
 *  version {{{ 0.6.0 }}}
 *  requires {{{ bw_common bw_math }}}
 *  description {{{
 *    One-pole (6 dB/oct) lowpass filter with unitary DC gain, separate attack
 *    and decay time constants, and sticky target-reach threshold.
 *
 *    This is better suited to implement smoothing than [bw_lp1](bw_lp1).
 *  }}}
 *  changelog {{{
 *    <ul>
 *      <li>Version <strong>0.6.0</strong>:
 *        <ul>
 *          <li><code>bw_one_pole_process()</code> and
 *              <code>bw_one_pole_process_multi()</code> now use
 *              <code>BW_SIZE_T</code> to count samples and channels.</li>
 *          <li>Added debugging code.</li>
 *          <li>Removed dependency on bw_config.</li>
 *          <li>Fixed bug when setting very high cutoff values.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.5.0</strong>:
 *        <ul>
 *          <li>Added <code>bw_one_pole_process_multi()</code>.</li>
 *          <li>Added C++ wrapper.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.4.0</strong>:
 *        <ul>
 *          <li>Fixed unused parameter warnings.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.2.0</strong>:
 *        <ul>
 *          <li>Refactored API.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.1.0</strong>:
 *        <ul>
 *          <li>First release.</li>
 *        </ul>
 *      </li>
 *    </ul>
 *  }}}
 */

#ifndef _BW_ONE_POLE_H
#define _BW_ONE_POLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bw_common.h>

/*! api {{{
 *    #### bw_one_pole_coeffs
 *  ```>>> */
typedef struct _bw_one_pole_coeffs bw_one_pole_coeffs;
/*! <<<```
 *    Coefficients and related.
 *
 *    #### bw_one_pole_state
 *  ```>>> */
typedef struct _bw_one_pole_state bw_one_pole_state;
/*! <<<```
 *    Internal state and related.
 *
 *    #### bw_one_pole_sticky_mode
 *  ```>>> */
typedef enum {
	bw_one_pole_sticky_mode_abs,
	bw_one_pole_sticky_mode_rel
} bw_one_pole_sticky_mode;
/*! <<<```
 *    Distance metrics for sticky behavior:
 *     * `bw_one_pole_sticky_mode_abs`: absolute difference (|`out` - `in`|);
 *     * `bw_one_pole_sticky_mode_rel`: relative difference with respect to
 *       input (|`out` - `in`| / |`in`|).
 *
 *    #### bw_one_pole_init()
 *  ```>>> */
static inline void bw_one_pole_init(bw_one_pole_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Initializes input parameter values in `coeffs`.
 *
 *    #### bw_one_pole_set_sample_rate()
 *  ```>>> */
static inline void bw_one_pole_set_sample_rate(bw_one_pole_coeffs *BW_RESTRICT coeffs, float sample_rate);
/*! <<<```
 *    Sets the `sample_rate` (Hz) value in `coeffs`.
 *
 *    #### bw_one_pole_reset_coeffs()
 *  ```>>> */
static inline void bw_one_pole_reset_coeffs(bw_one_pole_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Resets coefficients in `coeffs` to assume their target values.
 *
 *    #### bw_one_pole_reset_state()
 *  ```>>> */
static inline void bw_one_pole_reset_state(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float y_z1);
/*! <<<```
 *    Resets the given `state` to its initial values using the given `coeffs`
 *    and the quiescent/equilibrium value `y_z1`.
 *
 *    #### bw_one_pole_update_coeffs_ctrl()
 *  ```>>> */
static inline void bw_one_pole_update_coeffs_ctrl(bw_one_pole_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Triggers control-rate update of coefficients in `coeffs`.
 *
 *    #### bw_one_pole_update_coeffs_audio()
 *  ```>>> */
static inline void bw_one_pole_update_coeffs_audio(bw_one_pole_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Triggers audio-rate update of coefficients in `coeffs`.
 *
 *    #### bw_one_pole_process1\*()
 *  ```>>> */
static inline float bw_one_pole_process1(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float x);
static inline float bw_one_pole_process1_sticky_abs(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float x);
static inline float bw_one_pole_process1_sticky_rel(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float x);
static inline float bw_one_pole_process1_asym(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float x);
static inline float bw_one_pole_process1_asym_sticky_abs(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float x);
static inline float bw_one_pole_process1_asym_sticky_rel(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float x);
/*! <<<```
 *    These functions process one input sample `x` using `coeffs`, while using
 *    and updating `state`. They return the corresponding output sample.
 *
 *    In particular:
 *     * `bw_one_pole_process1()` assumes that upgoing and downgoing cutoff/tau
 *       are equal and the target-reach threshold is `0.f`;
 *     * `bw_one_pole_process1_sticky_abs()` assumes that upgoing and downgoing
 *       cutoff/tau are equal, that the target-reach threshold is not `0.f`,
 *       and that the distance metric for sticky behavior is set to
 *       `bw_one_pole_sticky_mode_abs`;
 *     * `bw_one_pole_process1_sticky_rel()` assumes that upgoing and downgoing
 *       cutoff/tau are equal, that the target-reach threshold is not `0.f`,
 *       and that the distance metric for sticky behavior is set to
 *       `bw_one_pole_sticky_mode_rel`;
 *     * `bw_one_pole_process1_asym()` assumes that upgoing and downgoing
 *       cutoff/tau are different and the target-reach threshold is `0.f`;
 *     * `bw_one_pole_process1_asym_sticky_abs()` assumes that upgoing and
 *       downgoing cutoff/tau are different, that the target-reach threshold is
 *       not `0.f`, and that the distance metric for sticky behavior is set to
 *       `bw_one_pole_sticky_mode_abs`;
 *     * `bw_one_pole_process1_asym_sticky_rel()` assumes that upgoing and
 *       downgoing cutoff/tau are different, that the target-reach threshold is
 *       not `0.f`, and that the distance metric for sticky behavior is set to
 *       `bw_one_pole_sticky_mode_rel`.
 *
 *    #### bw_one_pole_process()
 *  ```>>> */
static inline void bw_one_pole_process(bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, const float *x, float *y, BW_SIZE_T n_samples);
/*! <<<```
 *    Processes the first `n_samples` of the input buffer `x` and fills the
 *    first `n_samples` of the output buffer `y`, while using and updating both
 *    `coeffs` and `state` (control and audio rate).
 *
 *    `y` may be `NULL`.
 *
 *    #### bw_one_pole_process_multi()
 *  ```>>> */
static inline void bw_one_pole_process_multi(bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state **BW_RESTRICT state, const float **x, float **y, BW_SIZE_T n_channels, BW_SIZE_T n_samples);
/*! <<<```
 *    Processes the first `n_samples` of the `n_channels` input buffers `x` and
 *    fills the first `n_samples` of the `n_channels` output buffers `y`, while
 *    using and updating both the common `coeffs` and each of the `n_channels`
 *    `state`s (control and audio rate).
 *
 *    `y` or any element of `y` may be `NULL`.
 *
 *    #### bw_one_pole_set_cutoff()
 *  ```>>> */
static inline void bw_one_pole_set_cutoff(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets both the upgoing (attack) and downgoing (decay) cutoff frequency to
 *    the given `value` (Hz) in `coeffs`.
 *
 *    This is equivalent to calling both `bw_one_pole_set_cutoff_up()` and
 *    `bw_one_pole_set_cutoff_down()` with same `coeffs` and `value` or calling
 *    `bw_one_pole_set_tau()` with same `coeffs` and
 *    value = 1 / (2 * pi * `value`) (net of numerical errors).
 *
 *    Default value: `INFINITY`.
 *
 *    #### bw_one_pole_set_cutoff_up()
 *  ```>>> */
static inline void bw_one_pole_set_cutoff_up(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the upgoing (attack) cutoff frequency to the given `value` (Hz) in
 *    `coeffs`.
 *
 *    This is equivalent to calling `bw_one_pole_set_tau_up()` with same
 *    `coeffs` and value = 1 / (2 * pi * `value`) (net of numerical errors).
 *
 *    Default value: `INFINITY`.
 *
 *    #### bw_one_pole_set_cutoff_down()
 *  ```>>> */
static inline void bw_one_pole_set_cutoff_down(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the downgoing (attack) cutoff frequency to the given `value` (Hz) in
 *    `coeffs`.
 *
 *    This is equivalent to calling `bw_one_pole_set_tau_down()` with same
 *    `coeffs` and value = 1 / (2 * pi * `value`) (net of numerical errors).
 *
 *    Default value: `INFINITY`.
 *
 *    #### bw_one_pole_set_tau()
 *  ```>>> */
static inline void bw_one_pole_set_tau(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets both the upgoing (attack) and downgoing (decay) time constant to the
 *    given `value` (s) in `coeffs`.
 *
 *    This is equivalent to calling both `bw_one_pole_set_tau_up()` and
 *    `bw_one_pole_set_tau_down()` with same `coeffs` and `value` or calling
 *    `bw_one_pole_set_cutoff()` with same `coeffs` and
 *    value = 1 / (2 * pi * `value`) (net of numerical errors).
 *
 *    Default value: `0.f`.
 *
 *    #### bw_one_pole_set_tau_up()
 *  ```>>> */
static inline void bw_one_pole_set_tau_up(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the upgoing (attack) time constant to the given `value` (s) in
 *    `coeffs`.
 *
 *    This is equivalent to calling `bw_one_pole_set_cutoff_up()` with same
 *    `coeffs` and value = 1 / (2 * pi * `value`) (net of numerical errors).
 *
 *    Default value: `0.f`.
 *
 *    #### bw_one_pole_set_tau_down()
 *  ```>>> */
static inline void bw_one_pole_set_tau_down(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the downgoing (decay) time constant to the given `value` (s) in
 *    `coeffs`.
 *
 *    This is equivalent to calling `bw_one_pole_set_cutoff_down()` with same
 *    `coeffs` and value = 1 / (2 * pi * `value`) (net of numerical errors).
 *
 *    Default value: `0.f`.
 *
 *    #### bw_one_pole_set_sticky_thresh()
 *  ```>>> */
static inline void bw_one_pole_set_sticky_thresh(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the target-reach threshold specified by `value` in `coeffs`.
 *
 *    When the difference between the output and the input would fall under such
 *    threshold according to the current distance metric (see
 *    `bw_one_pole_set_sticky_mode()`), the output is forcefully set to be equal
 *    to the input value.
 *
 *    Default value: `0.f`.
 *
 *    #### bw_one_pole_set_sticky_mode()
 *  ```>>> */
static inline void bw_one_pole_set_sticky_mode(bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_sticky_mode value);
/*! <<<```
 *    Sets the current distance metric for sticky behavior to `value` in
 *    `coeffs`.
 *
 *    Default value: `bw_one_pole_sticky_mode_abs`.
 *
 *    #### bw_one_pole_get_y_z1()
 *  ```>>> */
static inline float bw_one_pole_get_y_z1(const bw_one_pole_state *BW_RESTRICT state);
/*! <<<```
 *    Returns the last output sample as stored in `state`.
 *
 *    #### bw_one_pole_coeffs_is_valid()
 *  ```>>> */
static inline char bw_one_pole_coeffs_is_valid(const bw_one_pole_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    WRITEME
 *
 *    #### bw_one_pole_state_is_valid()
 *  ```>>> */
static inline char bw_one_pole_state_is_valid(const bw_one_pole_state *BW_RESTRICT state);
/*! <<<```
 *    WRITEME
 *  }}} */

/*** Implementation ***/

/* WARNING: This part of the file is not part of the public API. Its content may
 * change at any time in future versions. Please, do not use it directly. */

#include <bw_math.h>

#ifdef BW_DEBUG_DEEP
enum _bw_one_pole_coeffs_state {
	_bw_one_pole_coeffs_state_invalid,
	_bw_one_pole_coeffs_state_init,
	_bw_one_pole_coeffs_state_set_sample_rate,
	_bw_one_pole_coeffs_state_reset_coeffs,
};
#endif

struct _bw_one_pole_coeffs {
#ifdef BW_DEBUG_DEEP
	uint32_t			hash;
	enum _bw_one_pole_coeffs_state	state;
	uint32_t			reset_id;
#endif

	// Coefficients
	float				Ttm2pi;

	float				mA1u;
	float				mA1d;
	float				st2;

	// Parameters
	float				cutoff_up;
	float				cutoff_down;
	float				sticky_thresh;
	bw_one_pole_sticky_mode		sticky_mode;
	int				param_changed;
};

struct _bw_one_pole_state {
#ifdef BW_DEBUG_DEEP
	uint32_t	hash;
	uint32_t	coeffs_reset_id;
#endif

	float		y_z1;
};

#define _BW_ONE_POLE_PARAM_CUTOFF_UP		1
#define _BW_ONE_POLE_PARAM_CUTOFF_DOWN		(1<<1)
#define _BW_ONE_POLE_PARAM_STICKY_THRESH	(1<<2)

static inline void bw_one_pole_init(bw_one_pole_coeffs *BW_RESTRICT coeffs) {
	BW_ASSERT(coeffs != NULL);

	coeffs->cutoff_up = INFINITY;
	coeffs->cutoff_down = INFINITY;
	coeffs->sticky_thresh = 0.f;
	coeffs->sticky_mode = bw_one_pole_sticky_mode_abs;

#ifdef BW_DEBUG_DEEP
	coeffs->hash = bw_hash_sdbm("bw_one_pole_coeffs");
	coeffs->state = _bw_one_pole_coeffs_state_init;
	coeffs->reset_id = coeffs->hash + 1;
#endif
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
}

static inline void bw_one_pole_set_sample_rate(bw_one_pole_coeffs *BW_RESTRICT coeffs, float sample_rate) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);

	coeffs->Ttm2pi = -6.283185307179586f / sample_rate;

#ifdef BW_DEBUG_DEEP
	coeffs->state = _bw_one_pole_coeffs_state_set_sample_rate;
#endif
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state == _bw_one_pole_coeffs_state_set_sample_rate);
}

static inline void _bw_one_pole_do_update_coeffs_ctrl(bw_one_pole_coeffs *BW_RESTRICT coeffs) {
	if (coeffs->param_changed) {
		if (coeffs->param_changed & _BW_ONE_POLE_PARAM_CUTOFF_UP)
			coeffs->mA1u = coeffs->cutoff_up > 1.591549430918953e8f ? 0.f : bw_expf_3(coeffs->Ttm2pi * coeffs->cutoff_up);
			// tau < 1 ns is instantaneous for any practical purpose
		if (coeffs->param_changed & _BW_ONE_POLE_PARAM_CUTOFF_DOWN)
			coeffs->mA1d = coeffs->cutoff_down > 1.591549430918953e8f ? 0.f : bw_expf_3(coeffs->Ttm2pi * coeffs->cutoff_down);
			// as before
		if (coeffs->param_changed & _BW_ONE_POLE_PARAM_STICKY_THRESH)
			coeffs->st2 = coeffs->sticky_thresh * coeffs->sticky_thresh;
		coeffs->param_changed = 0;
	}
}

static inline void bw_one_pole_reset_coeffs(bw_one_pole_coeffs *BW_RESTRICT coeffs) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_set_sample_rate);

	coeffs->param_changed = ~0;
	_bw_one_pole_do_update_coeffs_ctrl(coeffs);

#ifdef BW_DEBUG_DEEP
	coeffs->state = _bw_one_pole_coeffs_state_reset_coeffs;
	coeffs->reset_id++;
#endif
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state == _bw_one_pole_coeffs_state_reset_coeffs);
}

static inline void bw_one_pole_reset_state(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float y_z1) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT(state != NULL);
	BW_ASSERT(bw_is_finite(y_z1));

	(void)coeffs;
	state->y_z1 = y_z1;

#ifdef BW_DEBUG_DEEP
	state->hash = bw_hash_sdbm("bw_one_pole_state");
	state->coeffs_reset_id = coeffs->reset_id;
#endif
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
}

static inline void bw_one_pole_update_coeffs_ctrl(bw_one_pole_coeffs *BW_RESTRICT coeffs) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	
	_bw_one_pole_do_update_coeffs_ctrl(coeffs);
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
}

static inline void bw_one_pole_update_coeffs_audio(bw_one_pole_coeffs *BW_RESTRICT coeffs) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	
	(void)coeffs;
}

static inline float bw_one_pole_process1(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float x) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT(state != NULL);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT(bw_is_finite(x));
	
	const float y = x + coeffs->mA1u * (state->y_z1 - x);
	state->y_z1 = y;
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT(bw_is_finite(y));
	
	return y;
}

static inline float bw_one_pole_process1_sticky_abs(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float x) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT(state != NULL);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT(bw_is_finite(x));
	
	float y = x + coeffs->mA1u * (state->y_z1 - x);
	const float d = y - x;
	if (d * d <= coeffs->st2)
		y = x;
	state->y_z1 = y;
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT(bw_is_finite(y));
	
	return y;
}

static inline float bw_one_pole_process1_sticky_rel(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float x) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT(state != NULL);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT(bw_is_finite(x));
	
	float y = x + coeffs->mA1u * (state->y_z1 - x);
	const float d = y - x;
	if (d * d <= coeffs->st2 * x * x)
		y = x;
	state->y_z1 = y;
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT(bw_is_finite(y));
	
	return y;
}

static inline float bw_one_pole_process1_asym(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float x) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT(state != NULL);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT(bw_is_finite(x));
	
	const float y = x + (x >= state->y_z1 ? coeffs->mA1u : coeffs->mA1d) * (state->y_z1 - x);
	state->y_z1 = y;
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT(bw_is_finite(y));
	
	return y;
}

static inline float bw_one_pole_process1_asym_sticky_abs(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float x) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT(state != NULL);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT(bw_is_finite(x));
	
	float y = x + (x >= state->y_z1 ? coeffs->mA1u : coeffs->mA1d) * (state->y_z1 - x);
	const float d = y - x;
	if (d * d <= coeffs->st2)
		y = x;
	state->y_z1 = y;
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT(bw_is_finite(y));
	
	return y;
}

static inline float bw_one_pole_process1_asym_sticky_rel(const bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, float x) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT(state != NULL);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT(bw_is_finite(x));
	
	float y = x + (x >= state->y_z1 ? coeffs->mA1u : coeffs->mA1d) * (state->y_z1 - x);
	const float d = y - x;
	if (d * d <= coeffs->st2 * x * x)
		y = x;
	state->y_z1 = y;
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT(bw_is_finite(y));
	
	return y;
}

static inline void bw_one_pole_process(bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state *BW_RESTRICT state, const float *x, float *y, BW_SIZE_T n_samples) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT(state != NULL);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT(n_samples == 0 || x != NULL);
	BW_ASSERT_DEEP(!bw_has_nan(x, n_samples));
	
	bw_one_pole_update_coeffs_ctrl(coeffs);
	if (y != NULL) {
		if (coeffs->mA1u != coeffs->mA1d) {
			if (coeffs->st2 != 0.f) {
				if (coeffs->sticky_mode == bw_one_pole_sticky_mode_abs)
					for (BW_SIZE_T i = 0; i < n_samples; i++)
						y[i] = bw_one_pole_process1_asym_sticky_abs(coeffs, state, x[i]);
				else
					for (BW_SIZE_T i = 0; i < n_samples; i++)
						y[i] = bw_one_pole_process1_asym_sticky_rel(coeffs, state, x[i]);
			}
			else {
				for (BW_SIZE_T i = 0; i < n_samples; i++)
					y[i] = bw_one_pole_process1_asym(coeffs, state, x[i]);
			}
		}
		else {
			if (coeffs->st2 != 0.f) {
				if (coeffs->sticky_mode == bw_one_pole_sticky_mode_abs)
					for (BW_SIZE_T i = 0; i < n_samples; i++)
						y[i] = bw_one_pole_process1_sticky_abs(coeffs, state, x[i]);
				else
					for (BW_SIZE_T i = 0; i < n_samples; i++)
						y[i] = bw_one_pole_process1_sticky_rel(coeffs, state, x[i]);
			}
			else {
				for (BW_SIZE_T i = 0; i < n_samples; i++)
					y[i] = bw_one_pole_process1(coeffs, state, x[i]);
			}
		}
	} else {
		if (coeffs->mA1u != coeffs->mA1d) {
			if (coeffs->st2 != 0.f) {
				if (coeffs->sticky_mode == bw_one_pole_sticky_mode_abs)
					for (BW_SIZE_T i = 0; i < n_samples; i++)
						bw_one_pole_process1_asym_sticky_abs(coeffs, state, x[i]);
				else
					for (BW_SIZE_T i = 0; i < n_samples; i++)
						bw_one_pole_process1_asym_sticky_rel(coeffs, state, x[i]);
			}
			else {
				for (BW_SIZE_T i = 0; i < n_samples; i++)
					bw_one_pole_process1_asym(coeffs, state, x[i]);
			}
		}
		else {
			if (coeffs->st2 != 0.f) {
				if (coeffs->sticky_mode == bw_one_pole_sticky_mode_abs)
					for (BW_SIZE_T i = 0; i < n_samples; i++)
						bw_one_pole_process1_sticky_abs(coeffs, state, x[i]);
				else
					for (BW_SIZE_T i = 0; i < n_samples; i++)
						bw_one_pole_process1_sticky_rel(coeffs, state, x[i]);
			}
			else {
				for (BW_SIZE_T i = 0; i < n_samples; i++)
					bw_one_pole_process1(coeffs, state, x[i]);
			}
		}
	}
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	BW_ASSERT_DEEP(coeffs->reset_id == state->coeffs_reset_id);
	BW_ASSERT_DEEP(!bw_has_nan(y, n_samples));
}

static inline void bw_one_pole_process_multi(bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_state **BW_RESTRICT state, const float **x, float **y, BW_SIZE_T n_channels, BW_SIZE_T n_samples) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_reset_coeffs);
	//...
	
	bw_one_pole_update_coeffs_ctrl(coeffs);
	if (y != NULL) {
		if (coeffs->mA1u != coeffs->mA1d) {
			if (coeffs->st2 != 0.f) {
				if (coeffs->sticky_mode == bw_one_pole_sticky_mode_abs)
					for (BW_SIZE_T j = 0; j < n_channels; j++)
						if (y[j] != NULL)
							for (BW_SIZE_T i = 0; i < n_samples; i++)
								y[j][i] = bw_one_pole_process1_asym_sticky_abs(coeffs, state[j], x[j][i]);
						else
							for (BW_SIZE_T i = 0; i < n_samples; i++)
								bw_one_pole_process1_asym_sticky_abs(coeffs, state[j], x[j][i]);
						
				else
					for (BW_SIZE_T j = 0; j < n_channels; j++)
						if (y[j] != NULL)
							for (BW_SIZE_T i = 0; i < n_samples; i++)
								y[j][i] = bw_one_pole_process1_asym_sticky_rel(coeffs, state[j], x[j][i]);
						else
							for (BW_SIZE_T i = 0; i < n_samples; i++)
								bw_one_pole_process1_asym_sticky_rel(coeffs, state[j], x[j][i]);
			}
			else {
				for (BW_SIZE_T j = 0; j < n_channels; j++)
					if (y[j] != NULL)
						for (BW_SIZE_T i = 0; i < n_samples; i++)
							y[j][i] = bw_one_pole_process1_asym(coeffs, state[j], x[j][i]);
					else
						for (BW_SIZE_T i = 0; i < n_samples; i++)
							bw_one_pole_process1_asym(coeffs, state[j], x[j][i]);
			}
		}
		else {
			if (coeffs->st2 != 0.f) {
				if (coeffs->sticky_mode == bw_one_pole_sticky_mode_abs)
					for (BW_SIZE_T j = 0; j < n_channels; j++)
						if (y[j] != NULL)
							for (BW_SIZE_T i = 0; i < n_samples; i++)
								y[j][i] = bw_one_pole_process1_sticky_abs(coeffs, state[j], x[j][i]);
						else
							for (BW_SIZE_T i = 0; i < n_samples; i++)
								bw_one_pole_process1_sticky_abs(coeffs, state[j], x[j][i]);
				else
					for (BW_SIZE_T j = 0; j < n_channels; j++)
						if (y[j] != NULL)
							for (BW_SIZE_T i = 0; i < n_samples; i++)
								y[j][i] = bw_one_pole_process1_sticky_rel(coeffs, state[j], x[j][i]);
						else
							for (BW_SIZE_T i = 0; i < n_samples; i++)
								bw_one_pole_process1_sticky_rel(coeffs, state[j], x[j][i]);
			}
			else {
				for (BW_SIZE_T j = 0; j < n_channels; j++)
					if (y[j] != NULL)
						for (BW_SIZE_T i = 0; i < n_samples; i++)
							y[j][i] = bw_one_pole_process1(coeffs, state[j], x[j][i]);
					else
						for (BW_SIZE_T i = 0; i < n_samples; i++)
							bw_one_pole_process1(coeffs, state[j], x[j][i]);
			}
		}
	} else {
		if (coeffs->mA1u != coeffs->mA1d) {
			if (coeffs->st2 != 0.f) {
				if (coeffs->sticky_mode == bw_one_pole_sticky_mode_abs)
					for (BW_SIZE_T i = 0; i < n_samples; i++)
						for (BW_SIZE_T j = 0; j < n_channels; j++)
							bw_one_pole_process1_asym_sticky_abs(coeffs, state[j], x[j][i]);
				else
					for (BW_SIZE_T i = 0; i < n_samples; i++)
						for (BW_SIZE_T j = 0; j < n_channels; j++)
							bw_one_pole_process1_asym_sticky_rel(coeffs, state[j], x[j][i]);
			}
			else {
				for (BW_SIZE_T i = 0; i < n_samples; i++)
					for (BW_SIZE_T j = 0; j < n_channels; j++)
						bw_one_pole_process1_asym(coeffs, state[j], x[j][i]);
			}
		}
		else {
			if (coeffs->st2 != 0.f) {
				if (coeffs->sticky_mode == bw_one_pole_sticky_mode_abs)
					for (BW_SIZE_T i = 0; i < n_samples; i++)
						for (BW_SIZE_T j = 0; j < n_channels; j++)
							bw_one_pole_process1_sticky_abs(coeffs, state[j], x[j][i]);
				else
					for (BW_SIZE_T i = 0; i < n_samples; i++)
						for (BW_SIZE_T j = 0; j < n_channels; j++)
							bw_one_pole_process1_sticky_rel(coeffs, state[j], x[j][i]);
			}
			else {
				for (BW_SIZE_T i = 0; i < n_samples; i++)
					for (BW_SIZE_T j = 0; j < n_channels; j++)
						bw_one_pole_process1(coeffs, state[j], x[j][i]);
			}
		}
	}
	
	//...
}

static inline void bw_one_pole_set_cutoff(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
	BW_ASSERT(!bw_is_nan(value));
	BW_ASSERT(value >= 0.f);
	
	bw_one_pole_set_cutoff_up(coeffs, value);
	bw_one_pole_set_cutoff_down(coeffs, value);
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
}

static inline void bw_one_pole_set_cutoff_up(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
	BW_ASSERT(!bw_is_nan(value));
	BW_ASSERT(value >= 0.f);
	
	if (coeffs->cutoff_up != value) {
		coeffs->cutoff_up = value;
		coeffs->param_changed |= _BW_ONE_POLE_PARAM_CUTOFF_UP;
	}
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
}

static inline void bw_one_pole_set_cutoff_down(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
	BW_ASSERT(!bw_is_nan(value));
	BW_ASSERT(value >= 0.f);
	
	if (coeffs->cutoff_down != value) {
		coeffs->cutoff_down = value;
		coeffs->param_changed |= _BW_ONE_POLE_PARAM_CUTOFF_DOWN;
	}
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
}

static inline void bw_one_pole_set_tau(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
	BW_ASSERT(!bw_is_nan(value));
	BW_ASSERT(value >= 0.f);
	
	bw_one_pole_set_tau_up(coeffs, value);
	bw_one_pole_set_tau_down(coeffs, value);
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
}

static inline void bw_one_pole_set_tau_up(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
	BW_ASSERT(!bw_is_nan(value));
	BW_ASSERT(value >= 0.f);
	
	bw_one_pole_set_cutoff_up(coeffs, value < 1e-9f ? INFINITY : 0.1591549430918953f * bw_rcpf_2(value));
	// tau < 1 ns is instantaneous for any practical purpose
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
}

static inline void bw_one_pole_set_tau_down(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
	BW_ASSERT(!bw_is_nan(value));
	BW_ASSERT(value >= 0.f);
	
	bw_one_pole_set_cutoff_down(coeffs, value < 1e-9f ? INFINITY : 0.1591549430918953f * bw_rcpf_2(value));
	// as before
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
}

static inline void bw_one_pole_set_sticky_thresh(bw_one_pole_coeffs *BW_RESTRICT coeffs, float value) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
	//...
	
	if (coeffs->sticky_thresh != value) {
		coeffs->sticky_thresh = value;
		coeffs->param_changed |= _BW_ONE_POLE_PARAM_STICKY_THRESH;
	}
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
}

static inline void bw_one_pole_set_sticky_mode(bw_one_pole_coeffs *BW_RESTRICT coeffs, bw_one_pole_sticky_mode value) {
	BW_ASSERT(coeffs != NULL);
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
	//...
	
	coeffs->sticky_mode = value;
	
	BW_ASSERT_DEEP(bw_one_pole_coeffs_is_valid(coeffs));
	BW_ASSERT_DEEP(coeffs->state >= _bw_one_pole_coeffs_state_init);
}

static inline float bw_one_pole_get_y_z1(const bw_one_pole_state *BW_RESTRICT state) {
	BW_ASSERT(state != NULL);
	BW_ASSERT_DEEP(bw_one_pole_state_is_valid(state));
	
	return state->y_z1;
}

static inline char bw_one_pole_coeffs_is_valid(const bw_one_pole_coeffs *BW_RESTRICT coeffs) {
	BW_ASSERT(coeffs != NULL);

#ifdef BW_DEBUG_DEEP
	if (coeffs->hash != bw_hash_sdbm("bw_one_pole_coeffs"))
		return 0;
#endif
	(void)coeffs;
	//...

	return 1;
}

static inline char bw_one_pole_state_is_valid(const bw_one_pole_state *BW_RESTRICT state) {
	BW_ASSERT(state != NULL);

#ifdef BW_DEBUG_DEEP
	if (state->hash != bw_hash_sdbm("bw_one_pole_state"))
		return 0;
#endif

	return bw_is_finite(state->y_z1);
}

#undef _BW_ONE_POLE_PARAM_CUTOFF_UP
#undef _BW_ONE_POLE_PARAM_CUTOFF_DOWN
#undef _BW_ONE_POLE_PARAM_STICKY_THRESH

#ifdef __cplusplus
}
#endif

#endif
