#ifdef CONFIG_BAND_SBAND
if (state->current_band == BAND_SBAND) {
			dib0090_set_rframp(state, rf_ramp_sband);
			dib0090_set_bbramp(state, bb_ramp_boost);
		} else
#endif
#ifdef CONFIG_BAND_VHF
		if (state->current_band == BAND_VHF && !state->identity.p1g) {
			dib0090_set_rframp(state, rf_ramp_pwm_vhf);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal);
		} else
#endif
#ifdef CONFIG_BAND_CBAND
		if (state->current_band == BAND_CBAND && !state->identity.p1g) {
			dib0090_set_rframp(state, rf_ramp_pwm_cband);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal);
		} else
#endif
		if ((state->current_band == BAND_CBAND || state->current_band == BAND_VHF) && state->identity.p1g) {
			dib0090_set_rframp(state, rf_ramp_pwm_cband_7090p);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal_socs);
		} else {
			dib0090_set_rframp(state, rf_ramp_pwm_uhf);
			dib0090_set_bbramp(state, bb_ramp_pwm_normal);
		}
