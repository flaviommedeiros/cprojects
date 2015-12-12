switch (effectvalue >> 4) {
						//case IT_S_SET_FILTER:
							/* Waveforms for commands S3x, S4x and S5x:
							 *   0: Sine wave
							 *   1: Ramp down
							 *   2: Square wave
							 *   3: Random wave
							 */
						case IT_S_SET_GLISSANDO_CONTROL:
							channel->glissando = effectvalue & 15;
							break;

						case IT_S_FINETUNE:
							if (channel->playing) {
								channel->playing->finetune = ((int)(effectvalue & 15) - 8) << 5;
							}
							break;

						case IT_S_SET_VIBRATO_WAVEFORM:
							{
								int waveform = effectvalue & 3;
								if (sigdata->flags & IT_WAS_A_MOD) waveform = mod_convert_vibrato[waveform];
								else if (sigdata->flags & IT_WAS_AN_XM) waveform = xm_convert_vibrato[waveform];
								channel->vibrato_waveform = waveform;
								if (channel->playing) {
									channel->playing->vibrato_waveform = waveform;
									if (!(effectvalue & 4))
										channel->playing->vibrato_time = 0;
								}
							}
							break;
						case IT_S_SET_TREMOLO_WAVEFORM:
							{
								int waveform = effectvalue & 3;
								if (sigdata->flags & IT_WAS_A_MOD) waveform = mod_convert_vibrato[waveform];
								else if (sigdata->flags & IT_WAS_AN_XM) waveform = xm_convert_vibrato[waveform];
								channel->tremolo_waveform = waveform;
								if (channel->playing) {
									channel->playing->tremolo_waveform = waveform;
									if (!(effectvalue & 4))
										channel->playing->tremolo_time = 0;
								}
							}
							break;
						case IT_S_SET_PANBRELLO_WAVEFORM:
							channel->panbrello_waveform = effectvalue & 3;
							if (channel->playing) {
								channel->playing->panbrello_waveform = effectvalue & 3;
								if (!(effectvalue & 4))
									channel->playing->panbrello_time = 0;
							}
							break;

						case IT_S_FINE_PATTERN_DELAY:
							sigrenderer->tick += effectvalue & 15;
							break;
#if 1
						case IT_S7:
							{
								if (sigrenderer->sigdata->flags & IT_USE_INSTRUMENTS)
								{
									int i;
									switch (effectvalue & 15)
									{
									case 0: /* cut background notes */
										for (i = 0; i < DUMB_IT_N_NNA_CHANNELS; i++)
										{
											IT_PLAYING * playing = sigrenderer->playing[i];
											if (playing && channel == playing->channel)
											{
												playing->declick_stage = 3;
												if (channel->playing == playing) channel->playing = NULL;
											}
										}
										break;
									case 1: /* release background notes */
										for (i = 0; i < DUMB_IT_N_NNA_CHANNELS; i++)
										{
											IT_PLAYING * playing = sigrenderer->playing[i];
											if (playing && channel == playing->channel && !(playing->flags & IT_PLAYING_SUSTAINOFF))
											{
												it_note_off(playing);
											}
										}
										break;
									case 2: /* fade background notes */
										for (i = 0; i < DUMB_IT_N_NNA_CHANNELS; i++)
										{
											IT_PLAYING * playing = sigrenderer->playing[i];
											if (playing && channel == playing->channel)
											{
												//playing->flags &= IT_PLAYING_SUSTAINOFF;
												playing->flags |= IT_PLAYING_FADING;
											}
										}
										break;
									case 3:
										channel->new_note_action = NNA_NOTE_CUT;
										break;
									case 4:
										channel->new_note_action = NNA_NOTE_CONTINUE;
										break;
									case 5:
										channel->new_note_action = NNA_NOTE_OFF;
										break;
									case 6:
										channel->new_note_action = NNA_NOTE_FADE;
										break;

									case 7:
										if (channel->playing)
											channel->playing->enabled_envelopes &= ~IT_ENV_VOLUME;
										break;
									case 8:
										if (channel->playing)
											channel->playing->enabled_envelopes |= IT_ENV_VOLUME;
										break;

									case 9:
										if (channel->playing)
											channel->playing->enabled_envelopes &= ~IT_ENV_PANNING;
										break;
									case 10:
										if (channel->playing)
											channel->playing->enabled_envelopes |= IT_ENV_PANNING;
										break;

									case 11:
										if (channel->playing)
											channel->playing->enabled_envelopes &= ~IT_ENV_PITCH;
										break;
									case 12:
										if (channel->playing)
											channel->playing->enabled_envelopes |= IT_ENV_PITCH;
										break;
									}
								}
							}
							break;
#endif
						case IT_S_SET_PAN:
							//ASSERT(!(sigdata->flags & IT_WAS_AN_XM));
							channel->pan =
								((effectvalue & 15) << 2) |
								((effectvalue & 15) >> 2);
							channel->truepan = channel->pan << IT_ENVELOPE_SHIFT;

							if (channel->playing)
								channel->playing->panbrello_depth = 0;
							break;
						case IT_S_SET_SURROUND_SOUND:
							if ((effectvalue & 15) == 15) {
								if (channel->playing && channel->playing->sample &&
									!(channel->playing->sample->flags & (IT_SAMPLE_LOOP | IT_SAMPLE_SUS_LOOP))) {
									channel->playing->flags |= IT_PLAYING_REVERSE;
									it_playing_reset_resamplers( channel->playing, channel->playing->sample->length - 1 );
								}
							} else if ((effectvalue & 15) == 1) {
								channel->pan = IT_SURROUND;
								channel->truepan = channel->pan << IT_ENVELOPE_SHIFT;
							}
							if (channel->playing)
								channel->playing->panbrello_depth = 0;
							break;
						case IT_S_SET_HIGH_OFFSET:
							channel->high_offset = effectvalue & 15;
							break;
						//case IT_S_PATTERN_LOOP:
						case IT_S_DELAYED_NOTE_CUT:
							channel->note_cut_count = effectvalue & 15;
							if (!channel->note_cut_count) {
								if (sigdata->flags & (IT_WAS_AN_XM | IT_WAS_A_PTM))
									channel->volume = 0;
								else
									channel->note_cut_count = 1;
							}
							break;
						case IT_S_SET_MIDI_MACRO:
							if ((sigdata->flags & (IT_WAS_AN_XM | IT_WAS_A_MOD)) == (IT_WAS_AN_XM | IT_WAS_A_MOD)) {
								channel->inv_loop_speed = effectvalue & 15;
								update_invert_loop(channel, channel->playing ? channel->playing->sample : NULL);
							} else channel->SFmacro = effectvalue & 15;
							break;
					}
