#ifdef PMAC_AMP_AVAIL
if (chip->mixer_data) {
		/* use amplifier.  the signal is connected from route A
		 * to the amp.  the amp has its headphone and speaker
		 * volumes and mute switches, so we use them instead of
		 * screamer registers.
		 * in this case, it seems the route C is not used.
		 */
		err = build_mixers(chip, ARRAY_SIZE(snd_pmac_awacs_amp_vol),
					snd_pmac_awacs_amp_vol);
		if (err < 0)
			return err;
		/* overwrite */
		chip->master_sw_ctl = snd_ctl_new1(&snd_pmac_awacs_amp_hp_sw,
							chip);
		err = snd_ctl_add(chip->card, chip->master_sw_ctl);
		if (err < 0)
			return err;
		chip->speaker_sw_ctl = snd_ctl_new1(&snd_pmac_awacs_amp_spk_sw,
							chip);
		err = snd_ctl_add(chip->card, chip->speaker_sw_ctl);
		if (err < 0)
			return err;
	} else
#endif /* PMAC_AMP_AVAIL */
	{
		/* route A = headphone, route C = speaker */
		err = snd_ctl_add(chip->card,
		    (speaker_vol = snd_ctl_new1(snd_pmac_awacs_speaker_vol,
						chip)));
		if (err < 0)
			return err;
		chip->speaker_sw_ctl = snd_ctl_new1(imac1
				? &snd_pmac_awacs_speaker_sw_imac1
				: imac2
				? &snd_pmac_awacs_speaker_sw_imac2
				: &snd_pmac_awacs_speaker_sw, chip);
		err = snd_ctl_add(chip->card, chip->speaker_sw_ctl);
		if (err < 0)
			return err;
	}
