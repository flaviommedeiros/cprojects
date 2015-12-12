switch (i) {
			case 'v': // Version
				return 0;
			case 'h': // help
				do_syntax();
				do_help();
				return 0;
			case 'r': // SoundCard Rate
				rate = atoi(optarg);
				break;
#ifdef EPERIMENT_626
			case 'b': // Reverb
				mixer_options ^= WM_MO_REVERB;
				break;
#endif
			case 'm': // Master Volume
				master_volume = (unsigned char)atoi(optarg);
				break;
			case 'o': // Wav Output
				strcpy(wav_file,optarg);
				break;
			case 'c': // Config File
				config_file = malloc (strlen(optarg)+1);
				strcpy(config_file,optarg);
				break;
			case 'd': // Output device
				pcmname = malloc (strlen(optarg)+1);
				strcpy(pcmname,optarg);
				break;
			case 'e': // Expensive Interpolation
				mixer_options |= WM_MO_EXPENSIVE_INTERPOLATION;
				break;
			case 'l': // linear volume
				mixer_options |= WM_MO_LINEAR_VOLUME;
				break;
			case 't': // play test midis
				test_midi = 1;
				break;
			case 'k': // set test bank
				test_bank = (unsigned char)atoi(optarg);
				break;
			case 'p': // set test patch
				test_patch = (unsigned char)atoi(optarg);
				break;
			default:
				printf ("Unknown Option -%o ??\n", i);
				return 0;
		}
