#ifdef CONFIG_BAND_CBAND
if (state->current_band == BAND_CBAND) {
			dib0090_set_rframp_pwm(state, rf_ramp_pwm_cband);
			dib0090_set_bbramp_pwm(state, bb_ramp_pwm_normal);
		} else
#endif
#ifdef CONFIG_BAND_VHF
		if (state->current_band == BAND_VHF) {
			dib0090_set_rframp_pwm(state, rf_ramp_pwm_vhf);
			dib0090_set_bbramp_pwm(state, bb_ramp_pwm_normal);
		} else
#endif
		{
			dib0090_set_rframp_pwm(state, rf_ramp_pwm_uhf);
			dib0090_set_bbramp_pwm(state, bb_ramp_pwm_normal);
		}
