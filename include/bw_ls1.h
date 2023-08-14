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
 *  requires {{{ bw_common bw_gain bw_lp1 bw_math bw_mm1 bw_one_pole }}}
 *  description {{{
 *    First-order low shelf filter (6 dB/oct) with gain asymptotically
 *    approaching unity as frequency increases.
 *  }}}
 *  changelog {{{
 *    <ul>
 *      <li>Version <strong>1.0.0</strong>:
 *        <ul>
 *          <li><code>bw_ls1_process()</code> and
 *              <code>bw_ls1_process_multi()</code> now use <code>size_t</code>
 *              to count samples and channels.</li>
 *          <li>Added more <code>const</code> and <code>BW_RESTRICT</code>
 *              specifiers to input arguments and implementation.</li>
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
 *          <li>Added <code>bw_ls1_process_multi()</code>.</li>
 *          <li>Added C++ wrapper.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.4.0</strong>:
 *        <ul>
 *          <li>Added initial input value to
 *              <code>bw_ls1_reset_state()</code>.</li>
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

#ifndef BW_LS1_H
#define BW_LS1_H

#include <bw_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! api {{{
 *    #### bw_ls1_coeffs
 *  ```>>> */
typedef struct bw_ls1_coeffs bw_ls1_coeffs;
/*! <<<```
 *    Coefficients and related.
 *
 *    #### bw_ls1_state
 *  ```>>> */
typedef struct bw_ls1_state bw_ls1_state;
/*! <<<```
 *    Internal state and related.
 *
 *    #### bw_ls1_init()
 *  ```>>> */
static inline void bw_ls1_init(bw_ls1_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Initializes input parameter values in `coeffs`.
 *
 *    #### bw_ls1_set_sample_rate()
 *  ```>>> */
static inline void bw_ls1_set_sample_rate(bw_ls1_coeffs *BW_RESTRICT coeffs, float sample_rate);
/*! <<<```
 *    Sets the `sample_rate` (Hz) value in `coeffs`.
 *
 *    #### bw_ls1_reset_coeffs()
 *  ```>>> */
static inline void bw_ls1_reset_coeffs(bw_ls1_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Resets coefficients in `coeffs` to assume their target values.
 *
 *    #### bw_ls1_reset_state()
 *  ```>>> */
static inline void bw_ls1_reset_state(const bw_ls1_coeffs *BW_RESTRICT coeffs, bw_ls1_state *BW_RESTRICT state, float x_0);
/*! <<<```
 *    Resets the given `state` to its initial values using the given `coeffs`
 *    and the quiescent/initial input value `x_0`.
 *
 *    #### bw_ls1_update_coeffs_ctrl()
 *  ```>>> */
static inline void bw_ls1_update_coeffs_ctrl(bw_ls1_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Triggers control-rate update of coefficients in `coeffs`.
 *
 *    #### bw_ls1_update_coeffs_audio()
 *  ```>>> */
static inline void bw_ls1_update_coeffs_audio(bw_ls1_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Triggers audio-rate update of coefficients in `coeffs`.
 *
 *    #### bw_ls1_process1()
 *  ```>>> */
static inline float bw_ls1_process1(const bw_ls1_coeffs *BW_RESTRICT coeffs, bw_ls1_state *BW_RESTRICT state, float x);
/*! <<<```
 *    Processes one input sample `x` using `coeffs`, while using and updating
 *    `state`. Returns the corresponding output sample.
 *
 *    #### bw_ls1_process()
 *  ```>>> */
static inline void bw_ls1_process(bw_ls1_coeffs *BW_RESTRICT coeffs, bw_ls1_state *BW_RESTRICT state, const float *x, float *y, size_t n_samples);
/*! <<<```
 *    Processes the first `n_samples` of the input buffer `x` and fills the
 *    first `n_samples` of the output buffer `y`, while using and updating both
 *    `coeffs` and `state` (control and audio rate).
 *
 *    #### bw_ls1_process_multi()
 *  ```>>> */
static inline void bw_ls1_process_multi(bw_ls1_coeffs *BW_RESTRICT coeffs, bw_ls1_state *BW_RESTRICT const *BW_RESTRICT state, const float * const *x, float * const *y, size_t n_channels, size_t n_samples);
/*! <<<```
 *    Processes the first `n_samples` of the `n_channels` input buffers `x` and
 *    fills the first `n_samples` of the `n_channels` output buffers `y`, while
 *    using and updating both the common `coeffs` and each of the `n_channels`
 *    `state`s (control and audio rate).
 *
 *    #### bw_ls1_set_cutoff()
 *  ```>>> */
static inline void bw_ls1_set_cutoff(bw_ls1_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the cutoff frequency `value` (Hz) in `coeffs`.
 *
 *    Default value: `1e3f`.
 *
 *    #### bw_ls1_set_dc_gain_lin()
 *  ```>>> */
static inline void bw_ls1_set_dc_gain_lin(bw_ls1_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the dc gain parameter to the given `value` (linear gain) in `coeffs`.
 *
 *    Default value: `0.f`.
 *
 *    #### bw_ls1_set_dc_gain_dB()
 *  ```>>> */
static inline void bw_ls1_set_dc_gain_dB(bw_ls1_coeffs *BW_RESTRICT coeffs, float value);
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

#include <bw_mm1.h>
#include <bw_math.h>

#ifdef __cplusplus
extern "C" {
#endif

struct bw_ls1_coeffs {
	// Sub-components
	bw_mm1_coeffs	mm1_coeffs;

	// Parameters
	float		cutoff;
	float		dc_gain;
	char		update;
};

struct bw_ls1_state {
	bw_mm1_state	mm1_state;
};

static inline void bw_ls1_init(bw_ls1_coeffs *BW_RESTRICT coeffs) {
	bw_mm1_init(&coeffs->mm1_coeffs);
	bw_mm1_set_prewarp_at_cutoff(&coeffs->mm1_coeffs, 0);
	bw_mm1_set_coeff_x(&coeffs->mm1_coeffs, 1.f);
	bw_mm1_set_coeff_lp(&coeffs->mm1_coeffs, 0.f);
	coeffs->cutoff = 1e3f;
	coeffs->dc_gain = 1.f;
}

static inline void bw_ls1_set_sample_rate(bw_ls1_coeffs *BW_RESTRICT coeffs, float sample_rate) {
	bw_mm1_set_sample_rate(&coeffs->mm1_coeffs, sample_rate);
}

static inline void bw_ls1_update_mm1_params(bw_ls1_coeffs *BW_RESTRICT coeffs) {
	if (coeffs->update) {
		bw_mm1_set_cutoff(&coeffs->mm1_coeffs, coeffs->cutoff * bw_rcpf(bw_sqrtf(coeffs->dc_gain)));
		bw_mm1_set_coeff_lp(&coeffs->mm1_coeffs, coeffs->dc_gain - 1.f);
		bw_mm1_set_prewarp_freq(&coeffs->mm1_coeffs, coeffs->cutoff);
		coeffs->update = 0;
	}
}

static inline void bw_ls1_reset_coeffs(bw_ls1_coeffs *BW_RESTRICT coeffs) {
	coeffs->update = 1;
	bw_ls1_update_mm1_params(coeffs);
	bw_mm1_reset_coeffs(&coeffs->mm1_coeffs);
}

static inline void bw_ls1_reset_state(const bw_ls1_coeffs *BW_RESTRICT coeffs, bw_ls1_state *BW_RESTRICT state, float x_0) {
	bw_mm1_reset_state(&coeffs->mm1_coeffs, &state->mm1_state, x_0);
}

static inline void bw_ls1_update_coeffs_ctrl(bw_ls1_coeffs *BW_RESTRICT coeffs) {
	bw_ls1_update_mm1_params(coeffs);
	bw_mm1_update_coeffs_ctrl(&coeffs->mm1_coeffs);
}

static inline void bw_ls1_update_coeffs_audio(bw_ls1_coeffs *BW_RESTRICT coeffs) {
	bw_mm1_update_coeffs_audio(&coeffs->mm1_coeffs);
}

static inline float bw_ls1_process1(const bw_ls1_coeffs *BW_RESTRICT coeffs, bw_ls1_state *BW_RESTRICT state, float x) {
	return bw_mm1_process1(&coeffs->mm1_coeffs, &state->mm1_state, x);
}

static inline void bw_ls1_process(bw_ls1_coeffs *BW_RESTRICT coeffs, bw_ls1_state *BW_RESTRICT state, const float *x, float *y, size_t n_samples) {
	bw_ls1_update_coeffs_ctrl(coeffs);
	for (size_t i = 0; i < n_samples; i++) {
		bw_ls1_update_coeffs_audio(coeffs);
		y[i] = bw_ls1_process1(coeffs, state, x[i]);
	}
}

static inline void bw_ls1_process_multi(bw_ls1_coeffs *BW_RESTRICT coeffs, bw_ls1_state *BW_RESTRICT const *BW_RESTRICT state, const float * const *x, float * const *y, size_t n_channels, size_t n_samples) {
	bw_ls1_update_coeffs_ctrl(coeffs);
	for (size_t i = 0; i < n_samples; i++) {
		bw_ls1_update_coeffs_audio(coeffs);
		for (size_t j = 0; j < n_channels; j++)
			y[j][i] = bw_ls1_process1(coeffs, state[j], x[j][i]);
	}
}

static inline void bw_ls1_set_cutoff(bw_ls1_coeffs *BW_RESTRICT coeffs, float value) {
	if (value != coeffs->cutoff) {
		coeffs->cutoff = value;
		coeffs->update = 1;
	}
}

static inline void bw_ls1_set_dc_gain_lin(bw_ls1_coeffs *BW_RESTRICT coeffs, float value) {
	if (value != coeffs->dc_gain) {
		coeffs->dc_gain = value;
		coeffs->update = 1;
	}
}

static inline void bw_ls1_set_dc_gain_dB(bw_ls1_coeffs *BW_RESTRICT coeffs, float value) {
	bw_ls1_set_dc_gain_lin(coeffs, bw_dB2linf(value));
}

#ifdef __cplusplus
}

#include <array>

namespace Brickworks {

/*** Public C++ API ***/

/*! api_cpp {{{
 *    ##### Brickworks::LS1
 *  ```>>> */
template<size_t N_CHANNELS>
class LS1 {
public:
	LS1();

	void setSampleRate(float sampleRate);
	void reset(float x_0 = 0.f);
	void process(
		const float * const *x,
		float * const *y,
		size_t nSamples);
	void process(
		std::array<const float *, N_CHANNELS> x,
		std::array<float *, N_CHANNELS> y,
		size_t nSamples);

	void setCutoff(float value);
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
	bw_ls1_coeffs	 coeffs;
	bw_ls1_state	 states[N_CHANNELS];
	bw_ls1_state	*BW_RESTRICT statesP[N_CHANNELS];
};

template<size_t N_CHANNELS>
inline LS1<N_CHANNELS>::LS1() {
	bw_ls1_init(&coeffs);
	for (size_t i = 0; i < N_CHANNELS; i++)
		statesP[i] = states + i;
}

template<size_t N_CHANNELS>
inline void LS1<N_CHANNELS>::setSampleRate(float sampleRate) {
	bw_ls1_set_sample_rate(&coeffs, sampleRate);
}

template<size_t N_CHANNELS>
inline void LS1<N_CHANNELS>::reset(float x_0) {
	bw_ls1_reset_coeffs(&coeffs);
	for (size_t i = 0; i < N_CHANNELS; i++)
		bw_ls1_reset_state(&coeffs, states + i, x_0);
}

template<size_t N_CHANNELS>
inline void LS1<N_CHANNELS>::process(
		const float * const *x,
		float * const *y,
		size_t nSamples) {
	bw_ls1_process_multi(&coeffs, statesP, x, y, N_CHANNELS, nSamples);
}

template<size_t N_CHANNELS>
inline void LS1<N_CHANNELS>::process(
		std::array<const float *, N_CHANNELS> x,
		std::array<float *, N_CHANNELS> y,
		size_t nSamples) {
	process(x.data(), y.data(), nSamples);
}

template<size_t N_CHANNELS>
inline void LS1<N_CHANNELS>::setCutoff(float value) {
	bw_ls1_set_cutoff(&coeffs, value);
}

template<size_t N_CHANNELS>
inline void LS1<N_CHANNELS>::setDcGainLin(float value) {
	bw_ls1_set_dc_gain_lin(&coeffs, value);
}

template<size_t N_CHANNELS>
inline void LS1<N_CHANNELS>::setDcGainDB(float value) {
	bw_ls1_set_dc_gain_dB(&coeffs, value);
}

}
#endif

#endif
