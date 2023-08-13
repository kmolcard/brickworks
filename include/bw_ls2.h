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
 *  version {{{ 1.0.0 }}}
 *  requires {{{ bw_common bw_gain bw_math bw_mm2 bw_one_pole bw_svf }}}
 *  description {{{
 *    Second-order low shelf filter (12 dB/oct) with gain asymptotically
 *    approaching unity as frequency increases.
 *  }}}
 *  changelog {{{
 *    <ul>
 *      <li>Version <strong>1.0.0</strong>:
 *        <ul>
 *          <li><code>bw_ls2_process()</code> and
 *              <code>bw_ls2_process_multi()</code> now use <code>size_t</code>
 *              to count samples and channels.</li>
 *          <li>Added more <code>const</code> specifiers to input
 *              arguments.</li>
 *          <li>Moved C++ code to C header.</li>
 *          <li>Added overladed C++ <code>process()</code> function taking
 *              C-style arrays as arguments.</li>
 *          <li>Removed usage of reserved identifiers.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.6.0</strong>:
 *        <ul>
 *          <li>Removed dependency on bw_config.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.5.0</strong>:
 *        <ul>
 *          <li>Added <code>bw_ls2_process_multi()</code>.</li>
 *          <li>Added C++ wrapper.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.4.0</strong>:
 *        <ul>
 *          <li>Added initial input value to
 *              <code>bw_ls2_reset_state()</code>.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.3.0</strong>:
 *        <ul>
 *          <li>First release.</li>
 *        </ul>
 *      </li>
 *    </ul>
 *  }}}
 */

#ifndef BW_LS2_H
#define BW_LS2_H

#include <bw_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! api {{{
 *    #### bw_ls2_coeffs
 *  ```>>> */
typedef struct bw_ls2_coeffs bw_ls2_coeffs;
/*! <<<```
 *    Coefficients and related.
 *
 *    #### bw_ls2_state
 *  ```>>> */
typedef struct bw_ls2_state bw_ls2_state;
/*! <<<```
 *    Internal state and related.
 *
 *    #### bw_ls2_init()
 *  ```>>> */
static inline void bw_ls2_init(bw_ls2_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Initializes input parameter values in `coeffs`.
 *
 *    #### bw_ls2_set_sample_rate()
 *  ```>>> */
static inline void bw_ls2_set_sample_rate(bw_ls2_coeffs *BW_RESTRICT coeffs, float sample_rate);
/*! <<<```
 *    Sets the `sample_rate` (Hz) value in `coeffs`.
 *
 *    #### bw_ls2_reset_coeffs()
 *  ```>>> */
static inline void bw_ls2_reset_coeffs(bw_ls2_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Resets coefficients in `coeffs` to assume their target values.
 *
 *    #### bw_ls2_reset_state()
 *  ```>>> */
static inline void bw_ls2_reset_state(const bw_ls2_coeffs *BW_RESTRICT coeffs, bw_ls2_state *BW_RESTRICT state, float x_0);
/*! <<<```
 *    Resets the given `state` to its initial values using the given `coeffs`
 *    and the quiescent/initial input value `x_0`.
 *
 *    #### bw_ls2_update_coeffs_ctrl()
 *  ```>>> */
static inline void bw_ls2_update_coeffs_ctrl(bw_ls2_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Triggers control-rate update of coefficients in `coeffs`.
 *
 *    #### bw_ls2_update_coeffs_audio()
 *  ```>>> */
static inline void bw_ls2_update_coeffs_audio(bw_ls2_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Triggers audio-rate update of coefficients in `coeffs`.
 *
 *    #### bw_ls2_process1()
 *  ```>>> */
static inline float bw_ls2_process1(const bw_ls2_coeffs *BW_RESTRICT coeffs, bw_ls2_state *BW_RESTRICT state, float x);
/*! <<<```
 *    Processes one input sample `x` using `coeffs`, while using and updating
 *    `state`. Returns the corresponding output sample.
 *
 *    #### bw_ls2_process()
 *  ```>>> */
static inline void bw_ls2_process(bw_ls2_coeffs *BW_RESTRICT coeffs, bw_ls2_state *BW_RESTRICT state, const float *x, float *y, size_t n_samples);
/*! <<<```
 *    Processes the first `n_samples` of the input buffer `x` and fills the
 *    first `n_samples` of the output buffer `y`, while using and updating both
 *    `coeffs` and `state` (control and audio rate).
 *
 *    #### bw_ls2_process_multi()
 *  ```>>> */
static inline void bw_ls2_process_multi(bw_ls2_coeffs *BW_RESTRICT coeffs, bw_ls2_state * const *BW_RESTRICT state, const float * const *x, float **y, size_t n_channels, size_t n_samples);
/*! <<<```
 *    Processes the first `n_samples` of the `n_channels` input buffers `x` and
 *    fills the first `n_samples` of the `n_channels` output buffers `y`, while
 *    using and updating both the common `coeffs` and each of the `n_channels`
 *    `state`s (control and audio rate).
 *
 *    #### bw_ls2_set_cutoff()
 *  ```>>> */
static inline void bw_ls2_set_cutoff(bw_ls2_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the cutoff frequency `value` (Hz) in `coeffs`.
 *
 *    Default value: `1e3f`.
 *
 *    #### bw_ls2_set_Q()
 *  ```>>> */
static inline void bw_ls2_set_Q(bw_ls2_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the quality factor to the given `value` in `coeffs`.
 *
 *    `value` must be equal or bigger than `0.5f`.
 *
 *    Default value: `0.5f`.
 *
 *    #### bw_ls2_set_dc_gain_lin()
 *  ```>>> */
static inline void bw_ls2_set_dc_gain_lin(bw_ls2_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the dc gain parameter to the given `value` (linear gain) in `coeffs`.
 *
 *    Default value: `0.f`.
 *
 *    #### bw_ls2_set_dc_gain_dB()
 *  ```>>> */
static inline void bw_ls2_set_dc_gain_dB(bw_ls2_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the dc gain parameter to the given `value` (dB) in `coeffs`.
 *
 *    Default value: `-INFINITY`.
 *  }}} */

#ifdef __cplusplus
}
#endif

/*** Implementation ***/

/* WARNING: This part of the file is not part of the public API. Its content may
 * change at any time in future versions. Please, do not use it directly. */

#include <bw_mm2.h>
#include <bw_math.h>

#ifdef __cplusplus
extern "C" {
#endif

struct bw_ls2_coeffs {
	// Sub-components
	bw_mm2_coeffs	mm2_coeffs;

	// Coefficients
	float		sg;
	float		issg;

	// Parameters
	float		dc_gain;
	float		cutoff;
	int		param_changed;
};

struct bw_ls2_state {
	bw_mm2_state	mm2_state;
};

#define BW_LS2_PARAM_DC_GAIN	1
#define BW_LS2_PARAM_CUTOFF	(1<<1)

static inline void bw_ls2_init(bw_ls2_coeffs *BW_RESTRICT coeffs) {
	bw_mm2_init(&coeffs->mm2_coeffs);
	bw_mm2_set_prewarp_at_cutoff(&coeffs->mm2_coeffs, 0);
	coeffs->dc_gain = 1.f;
	coeffs->cutoff = 1e3f;
}

static inline void bw_ls2_set_sample_rate(bw_ls2_coeffs *BW_RESTRICT coeffs, float sample_rate) {
	bw_mm2_set_sample_rate(&coeffs->mm2_coeffs, sample_rate);
}

static inline void bw_ls2_update_mm2_params(bw_ls2_coeffs *BW_RESTRICT coeffs) {
	if (coeffs->param_changed) {
		if (coeffs->param_changed & BW_LS2_PARAM_DC_GAIN) {
			coeffs->sg = bw_sqrtf(coeffs->dc_gain);
			coeffs->issg = bw_sqrtf(bw_rcpf(coeffs->sg));
			bw_mm2_set_coeff_x(&coeffs->mm2_coeffs, coeffs->sg);
			bw_mm2_set_coeff_lp(&coeffs->mm2_coeffs, coeffs->dc_gain - coeffs->sg);
			bw_mm2_set_coeff_hp(&coeffs->mm2_coeffs, 1.f - coeffs->sg);
		}
		if (coeffs->param_changed & BW_LS2_PARAM_CUTOFF)
			bw_mm2_set_prewarp_freq(&coeffs->mm2_coeffs, coeffs->cutoff);
		bw_mm2_set_cutoff(&coeffs->mm2_coeffs, coeffs->cutoff * coeffs->issg);
		coeffs->param_changed = 0;
	}
}

static inline void bw_ls2_reset_coeffs(bw_ls2_coeffs *BW_RESTRICT coeffs) {
	coeffs->param_changed = ~0;
	bw_ls2_update_mm2_params(coeffs);
	bw_mm2_reset_coeffs(&coeffs->mm2_coeffs);
}

static inline void bw_ls2_reset_state(const bw_ls2_coeffs *BW_RESTRICT coeffs, bw_ls2_state *BW_RESTRICT state, float x_0) {
	bw_mm2_reset_state(&coeffs->mm2_coeffs, &state->mm2_state, x_0);
}

static inline void bw_ls2_update_coeffs_ctrl(bw_ls2_coeffs *BW_RESTRICT coeffs) {
	bw_ls2_update_mm2_params(coeffs);
	bw_mm2_update_coeffs_ctrl(&coeffs->mm2_coeffs);
}

static inline void bw_ls2_update_coeffs_audio(bw_ls2_coeffs *BW_RESTRICT coeffs) {
	bw_mm2_update_coeffs_audio(&coeffs->mm2_coeffs);
}

static inline float bw_ls2_process1(const bw_ls2_coeffs *BW_RESTRICT coeffs, bw_ls2_state *BW_RESTRICT state, float x) {
	return bw_mm2_process1(&coeffs->mm2_coeffs, &state->mm2_state, x);
}

static inline void bw_ls2_process(bw_ls2_coeffs *BW_RESTRICT coeffs, bw_ls2_state *BW_RESTRICT state, const float *x, float *y, size_t n_samples) {
	bw_ls2_update_coeffs_ctrl(coeffs);
	for (size_t i = 0; i < n_samples; i++) {
		bw_ls2_update_coeffs_audio(coeffs);
		y[i] = bw_ls2_process1(coeffs, state, x[i]);
	}
}

static inline void bw_ls2_process_multi(bw_ls2_coeffs *BW_RESTRICT coeffs, bw_ls2_state * const *BW_RESTRICT state, const float * const *x, float **y, size_t n_channels, size_t n_samples) {
	bw_ls2_update_coeffs_ctrl(coeffs);
	for (size_t i = 0; i < n_samples; i++) {
		bw_ls2_update_coeffs_audio(coeffs);
		for (size_t j = 0; j < n_channels; j++)
			y[j][i] = bw_ls2_process1(coeffs, state[j], x[j][i]);
	}
}

static inline void bw_ls2_set_cutoff(bw_ls2_coeffs *BW_RESTRICT coeffs, float value) {
	if (coeffs->cutoff != value) {
		coeffs->cutoff = value;
		coeffs->param_changed |= BW_LS2_PARAM_CUTOFF;
	}
}

static inline void bw_ls2_set_Q(bw_ls2_coeffs *BW_RESTRICT coeffs, float value) {
	bw_mm2_set_Q(&coeffs->mm2_coeffs, value);
}

static inline void bw_ls2_set_dc_gain_lin(bw_ls2_coeffs *BW_RESTRICT coeffs, float value) {
	if (coeffs->dc_gain != value) {
		coeffs->dc_gain = value;
		coeffs->param_changed |= BW_LS2_PARAM_DC_GAIN;
	}
}

static inline void bw_ls2_set_dc_gain_dB(bw_ls2_coeffs *BW_RESTRICT coeffs, float value) {
	bw_ls2_set_dc_gain_lin(coeffs, bw_dB2linf(value));
}

#undef BW_LS2_PARAM_DC_GAIN
#undef BW_LS2_PARAM_CUTOFF

#ifdef __cplusplus
}

#include <array>

namespace Brickworks {

/*** Public C++ API ***/

/*! api_cpp {{{
 *    ##### Brickworks::LS2
 *  ```>>> */
template<size_t N_CHANNELS>
class LS2 {
public:
	LS2();

	void setSampleRate(float sampleRate);
	void reset(float x_0 = 0.f);
	void process(
		const float * const *x,
		float **y,
		size_t nSamples);
	void process(
		std::array<const float *, N_CHANNELS> x,
		std::array<float *, N_CHANNELS> y,
		size_t nSamples);

	void setCutoff(float value);
	void setQ(float value);
	void setDcGainLin(float value);
	void setDcGainDB(float value);
/*! <<<...
 *  }
 *  ```
 *  }}} */

/*** Implementation ***/

/* WARNING: This part of the file is not part of the public API. Its content may
 * change at any time in future versions. Please, do not use it directly. */

private:
	bw_ls2_coeffs	 coeffs;
	bw_ls2_state	 states[N_CHANNELS];
	bw_ls2_state	*statesP[N_CHANNELS];
};

template<size_t N_CHANNELS>
inline LS2<N_CHANNELS>::LS2() {
	bw_ls2_init(&coeffs);
	for (size_t i = 0; i < N_CHANNELS; i++)
		statesP[i] = states + i;
}

template<size_t N_CHANNELS>
inline void LS2<N_CHANNELS>::setSampleRate(float sampleRate) {
	bw_ls2_set_sample_rate(&coeffs, sampleRate);
}

template<size_t N_CHANNELS>
inline void LS2<N_CHANNELS>::reset(float x_0) {
	bw_ls2_reset_coeffs(&coeffs);
	for (size_t i = 0; i < N_CHANNELS; i++)
		bw_ls2_reset_state(&coeffs, states + i, x_0);
}

template<size_t N_CHANNELS>
inline void LS2<N_CHANNELS>::process(
		const float * const *x,
		float **y,
		size_t nSamples) {
	bw_ls2_process_multi(&coeffs, statesP, x, y, N_CHANNELS, nSamples);
}

template<size_t N_CHANNELS>
inline void LS2<N_CHANNELS>::process(
		std::array<const float *, N_CHANNELS> x,
		std::array<float *, N_CHANNELS> y,
		size_t nSamples) {
	process(x.data(), y.data(), nSamples);
}

template<size_t N_CHANNELS>
inline void LS2<N_CHANNELS>::setCutoff(float value) {
	bw_ls2_set_cutoff(&coeffs, value);
}

template<size_t N_CHANNELS>
inline void LS2<N_CHANNELS>::setQ(float value) {
	bw_ls2_set_Q(&coeffs, value);
}

template<size_t N_CHANNELS>
inline void LS2<N_CHANNELS>::setDcGainLin(float value) {
	bw_ls2_set_dc_gain_lin(&coeffs, value);
}

template<size_t N_CHANNELS>
inline void LS2<N_CHANNELS>::setDcGainDB(float value) {
	bw_ls2_set_dc_gain_dB(&coeffs, value);
}

}
#endif

#endif
