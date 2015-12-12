switch (ch) {
						case 'l':
							WildMidi_SetOption(midi_ptr, WM_MO_LINEAR_VOLUME, ((mixer_options & WM_MO_LINEAR_VOLUME) ^ WM_MO_LINEAR_VOLUME));
							mixer_options ^= WM_MO_LINEAR_VOLUME;
							break;
#ifdef EXPERIMENT_626
						case 'r':
							WildMidi_SetOption(midi_ptr, WM_MO_REVERB, ((mixer_options & WM_MO_REVERB) ^ WM_MO_REVERB));	
							mixer_options ^= WM_MO_REVERB;	
							break;
#endif
						case 'e':
							WildMidi_SetOption(midi_ptr, WM_MO_EXPENSIVE_INTERPOLATION, ((mixer_options & WM_MO_EXPENSIVE_INTERPOLATION) ^ WM_MO_EXPENSIVE_INTERPOLATION));	
							mixer_options ^= WM_MO_EXPENSIVE_INTERPOLATION;	
							break;
						case 'n':
							goto NEXTMIDI;
						case 'q':	
							printf("\n");
							WildMidi_Close(midi_ptr);
							WildMidi_Shutdown();
							printf("Shutting down Sound System\n");
							close_output();
#ifndef _WIN32
							if (isatty(my_tty))
								resetty();
#endif
							printf("\r\n");
							exit (0);
						case '-':	
							if (master_volume > 0) {
								master_volume--;
								WildMidi_MasterVolume(master_volume);
							}
							break;
						case '+':
							if (master_volume < 127) {
								master_volume++;
								WildMidi_MasterVolume(master_volume);
							}
							break;
					}
