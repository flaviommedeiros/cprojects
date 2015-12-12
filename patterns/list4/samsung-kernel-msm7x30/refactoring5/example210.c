#ifdef CONFIG_BAND_SBAND
if (state->current_band == BAND_SBAND) {
			dib0090_set_rframp(state, rf_ramp_sband);
			dib0090_set_bbramp(state, bb_ramp_boost);
		} else
#endif
#ifdef CONFIG_BAND_VHF
		if (state->current_band == BAND_VHF && !state->identity.p1g) {
			dib0090_set_rframp(state, rf_ramp_vhf);
			dib0090_set_bbramp(state, bb_ramp_boost);
		} else
#endif
#ifdef CONFIG_BAND_CBAND
		if (state->current_band == BAND_CBAND && !state->identity.p1g) {
			dib0090_set_rframp(state, rf_ramp_cband);
			dib0090_set_bbramp(state, bb_ramp_boost);
		} else
#endif
		if ((state->current_band == BAND_CBAND || state->current_band == BAND_VHF) && state->identity.p1g) {
			dib0090_set_rframp(state, rf_ramp_cband_broadmatching);
			dib0090_set_bbramp(state, bb_ramp_boost);
		} else {
			dib0090_set_rframp(state, rf_ramp_uhf);
			dib0090_set_bbramp(state, bb_ramp_boost);
		}
