#ifdef CONFIG_BAND_CBAND
if (state->current_band == BAND_CBAND) {
			if (state->identity.in_soc) {
				dib0090_set_bbramp_pwm(state, bb_ramp_pwm_normal_socs);
				if (state->identity.version == SOC_8090_P1G_11R1 || state->identity.version == SOC_8090_P1G_21R1)
					dib0090_set_rframp_pwm(state, rf_ramp_pwm_cband_8090);
				else if (state->identity.version == SOC_7090_P1G_11R1
						|| state->identity.version == SOC_7090_P1G_21R1) {
					if (state->config->is_dib7090e) {
						if (state->rf_ramp == NULL)
							dib0090_set_rframp_pwm(state, rf_ramp_pwm_cband_7090e_sensitivity);
						else
							dib0090_set_rframp_pwm(state, state->rf_ramp);
					} else
						dib0090_set_rframp_pwm(state, rf_ramp_pwm_cband_7090);
				}
			} else {
				dib0090_set_rframp_pwm(state, rf_ramp_pwm_cband);
				dib0090_set_bbramp_pwm(state, bb_ramp_pwm_normal);
			}
		} else
#endif
#ifdef CONFIG_BAND_VHF
		if (state->current_band == BAND_VHF) {
			if (state->identity.in_soc) {
				dib0090_set_bbramp_pwm(state, bb_ramp_pwm_normal_socs);
			} else {
				dib0090_set_rframp_pwm(state, rf_ramp_pwm_vhf);
				dib0090_set_bbramp_pwm(state, bb_ramp_pwm_normal);
			}
		} else
#endif
		{
			if (state->identity.in_soc) {
				if (state->identity.version == SOC_8090_P1G_11R1 || state->identity.version == SOC_8090_P1G_21R1)
					dib0090_set_rframp_pwm(state, rf_ramp_pwm_uhf_8090);
				else if (state->identity.version == SOC_7090_P1G_11R1 || state->identity.version == SOC_7090_P1G_21R1)
					dib0090_set_rframp_pwm(state, rf_ramp_pwm_uhf_7090);
				dib0090_set_bbramp_pwm(state, bb_ramp_pwm_normal_socs);
			} else {
				dib0090_set_rframp_pwm(state, rf_ramp_pwm_uhf);
				dib0090_set_bbramp_pwm(state, bb_ramp_pwm_normal);
			}
		}
