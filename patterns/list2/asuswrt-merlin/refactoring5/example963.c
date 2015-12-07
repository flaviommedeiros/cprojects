#ifdef PMAC_AMP_AVAIL
if (chip->mixer_data) {
			struct awacs_amp *amp = chip->mixer_data;
			int changed;
			if (snd_pmac_awacs_detect_headphone(chip)) {
				changed = toggle_amp_mute(amp, AMP_CH_HD, 0);
				changed |= toggle_amp_mute(amp, AMP_CH_SPK, 1);
			} else {
				changed = toggle_amp_mute(amp, AMP_CH_HD, 1);
				changed |= toggle_amp_mute(amp, AMP_CH_SPK, 0);
			}
			if (do_notify && ! changed)
				return;
		} else
#endif
		{
			int reg = chip->awacs_reg[1] | (MASK_HDMUTE|MASK_SPKMUTE);
			if (snd_pmac_awacs_detect_headphone(chip))
				reg &= ~MASK_HDMUTE;
			else
				reg &= ~MASK_SPKMUTE;
			if (do_notify && reg == chip->awacs_reg[1])
				return;
			snd_pmac_awacs_write_reg(chip, 1, reg);
		}
