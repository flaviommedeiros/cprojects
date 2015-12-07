switch (c) {
	case TIM_OPT_VOLUME:
		return parse_opt_A(arg);
	case TIM_OPT_DRUM_POWER:
		return parse_opt_drum_power(arg);
	case TIM_OPT_VOLUME_COMP:
		return parse_opt_volume_comp(arg);
	case TIM_OPT_ANTI_ALIAS:
		return parse_opt_a(arg);
	case TIM_OPT_BUFFER_FRAGS:
		return parse_opt_B(arg);
	case TIM_OPT_CONTROL_RATIO:
		return parse_opt_C(arg);
	case TIM_OPT_CONFIG_FILE:
		return parse_opt_c(arg);
	case TIM_OPT_DRUM_CHANNEL:
		return parse_opt_D(arg);
	case TIM_OPT_IFACE_PATH:
		return parse_opt_d(arg);
	case TIM_OPT_EXT:
		return parse_opt_E(arg);
	case TIM_OPT_MOD_WHEEL:
		return parse_opt_mod_wheel(arg);
	case TIM_OPT_PORTAMENTO:
		return parse_opt_portamento(arg);
	case TIM_OPT_VIBRATO:
		return parse_opt_vibrato(arg);
	case TIM_OPT_CH_PRESS:
		return parse_opt_ch_pressure(arg);
	case TIM_OPT_MOD_ENV:
		return parse_opt_mod_env(arg);
	case TIM_OPT_TRACE_TEXT:
		return parse_opt_trace_text(arg);
	case TIM_OPT_OVERLAP:
		return parse_opt_overlap_voice(arg);
	case TIM_OPT_TEMPER_CTRL:
		return parse_opt_temper_control(arg);
	case TIM_OPT_DEFAULT_MID:
		return parse_opt_default_mid(arg);
	case TIM_OPT_SYSTEM_MID:
		return parse_opt_system_mid(arg);
	case TIM_OPT_DEFAULT_BANK:
		return parse_opt_default_bank(arg);
	case TIM_OPT_FORCE_BANK:
		return parse_opt_force_bank(arg);
	case TIM_OPT_DEFAULT_PGM:
		return parse_opt_default_program(arg);
	case TIM_OPT_FORCE_PGM:
		return parse_opt_force_program(arg);
	case TIM_OPT_DELAY:
		return parse_opt_delay(arg);
	case TIM_OPT_CHORUS:
		return parse_opt_chorus(arg);
	case TIM_OPT_REVERB:
		return parse_opt_reverb(arg);
	case TIM_OPT_VOICE_LPF:
		return parse_opt_voice_lpf(arg);
	case TIM_OPT_NS:
		return parse_opt_noise_shaping(arg);
#ifndef FIXED_RESAMPLATION
	case TIM_OPT_RESAMPLE:
		return parse_opt_resample(arg);
#endif
	case TIM_OPT_EVIL:
		return parse_opt_e(arg);
	case TIM_OPT_FAST_PAN:
		return parse_opt_F(arg);
	case TIM_OPT_FAST_DECAY:
		return parse_opt_f(arg);
	case TIM_OPT_SPECTROGRAM:
		return parse_opt_g(arg);
	case TIM_OPT_KEYSIG:
		return parse_opt_H(arg);
	case TIM_OPT_HELP:
		return parse_opt_h(arg);
	case TIM_OPT_INTERFACE:
		return parse_opt_i(arg);
	case TIM_OPT_VERBOSE:
		return parse_opt_verbose(arg);
	case TIM_OPT_QUIET:
		return parse_opt_quiet(arg);
	case TIM_OPT_TRACE:
		return parse_opt_trace(arg);
	case TIM_OPT_LOOP:
		return parse_opt_loop(arg);
	case TIM_OPT_RANDOM:
		return parse_opt_random(arg);
	case TIM_OPT_SORT:
		return parse_opt_sort(arg);
#ifdef IA_ALSASEQ
	case TIM_OPT_BACKGROUND:
		return parse_opt_background(arg);
	case TIM_OPT_RT_PRIO:
		return parse_opt_rt_prio(arg);
	case TIM_OPT_SEQ_PORTS:
		return parse_opt_seq_ports(arg);
#endif
	case TIM_OPT_REALTIME_LOAD:
		return parse_opt_j(arg);
	case TIM_OPT_ADJUST_KEY:
		return parse_opt_K(arg);
	case TIM_OPT_VOICE_QUEUE:
		return parse_opt_k(arg);
	case TIM_OPT_PATCH_PATH:
		return parse_opt_L(arg);
	case TIM_OPT_PCM_FILE:
		return parse_opt_M(arg);
	case TIM_OPT_DECAY_TIME:
		return parse_opt_m(arg);
	case TIM_OPT_INTERPOLATION:
		return parse_opt_N(arg);
	case TIM_OPT_OUTPUT_MODE:
		return parse_opt_O(arg);
	case TIM_OPT_OUTPUT_STEREO:
		if (! strcmp(the_option->name, "output-mono"))
			/* --output-mono == --output-stereo=no */
			arg = "no";
		return parse_opt_output_stereo(arg);
	case TIM_OPT_OUTPUT_SIGNED:
		if (! strcmp(the_option->name, "output-unsigned"))
			/* --output-unsigned == --output-signed=no */
			arg = "no";
		return parse_opt_output_signed(arg);
	case TIM_OPT_OUTPUT_BITWIDTH:
		if (! strcmp(the_option->name, "output-16bit"))
			arg = "16bit";
		else if (! strcmp(the_option->name, "output-24bit"))
			arg = "24bit";
		else if (! strcmp(the_option->name, "output-8bit"))
			arg = "8bit";
		return parse_opt_output_bitwidth(arg);
	case TIM_OPT_OUTPUT_FORMAT:
		if (! strcmp(the_option->name, "output-linear"))
			arg = "linear";
		else if (! strcmp(the_option->name, "output-ulaw"))
			arg = "ulaw";
		else if (! strcmp(the_option->name, "output-alaw"))
			arg = "alaw";
		return parse_opt_output_format(arg);
	case TIM_OPT_OUTPUT_SWAB:
		return parse_opt_output_swab(arg);
#ifdef AU_FLAC
	case TIM_OPT_FLAC_VERIFY:
		return parse_opt_flac_verify(arg);
	case TIM_OPT_FLAC_PADDING:
		return parse_opt_flac_padding(arg);
	case TIM_OPT_FLAC_COMPLEVEL:
		return parse_opt_flac_complevel(arg);
#ifdef AU_OGGFLAC
	case TIM_OPT_FLAC_OGGFLAC:
		return parse_opt_flac_oggflac(arg);
#endif /* AU_OGGFLAC */
#endif /* AU_FLAC */
#ifdef AU_SPEEX
	case TIM_OPT_SPEEX_QUALITY:
		return parse_opt_speex_quality(arg);
	case TIM_OPT_SPEEX_VBR:
		return parse_opt_speex_vbr(arg);
	case TIM_OPT_SPEEX_ABR:
		return parse_opt_speex_abr(arg);
	case TIM_OPT_SPEEX_VAD:
		return parse_opt_speex_vad(arg);
	case TIM_OPT_SPEEX_DTX:
		return parse_opt_speex_dtx(arg);
	case TIM_OPT_SPEEX_COMPLEXITY:
		return parse_opt_speex_complexity(arg);
	case TIM_OPT_SPEEX_NFRAMES:
		return parse_opt_speex_nframes(arg);
#endif /* AU_SPEEX */
	case TIM_OPT_OUTPUT_FILE:
		return parse_opt_o(arg);
	case TIM_OPT_PATCH_FILE:
		return parse_opt_P(arg);
	case TIM_OPT_POLYPHONY:
		return parse_opt_p(arg);
	case TIM_OPT_POLY_REDUCE:
		return parse_opt_p1(arg);
	case TIM_OPT_MUTE:
		return parse_opt_Q(arg);
	case TIM_OPT_TEMPER_MUTE:
		return parse_opt_Q1(arg);
	case TIM_OPT_AUDIO_BUFFER:
		return parse_opt_q(arg);
	case TIM_OPT_CACHE_SIZE:
		return parse_opt_S(arg);
	case TIM_OPT_SAMPLE_FREQ:
		return parse_opt_s(arg);
	case TIM_OPT_ADJUST_TEMPO:
		return parse_opt_T(arg);
	case TIM_OPT_CHARSET:
		return parse_opt_t(arg);
	case TIM_OPT_UNLOAD_INST:
		return parse_opt_U(arg);
	case TIM_OPT_VOLUME_CURVE:
		return parse_opt_volume_curve(arg);
	case TIM_OPT_VERSION:
		return parse_opt_v(arg);
#ifdef __W32__
	case TIM_OPT_RCPCV_DLL:
		return parse_opt_w(arg);
#endif
	case TIM_OPT_CONFIG_STR:
		return parse_opt_x(arg);
	case TIM_OPT_FREQ_TABLE:
		return parse_opt_Z(arg);
	case TIM_OPT_PURE_INT:
		return parse_opt_Z1(arg);
	case TIM_OPT_MODULE:
		return parse_opt_default_module(arg);
	default:
		ctl->cmsg(CMSG_FATAL, VERB_NORMAL,
				"[BUG] Inconceivable case branch %d", c);
		abort();
	}
