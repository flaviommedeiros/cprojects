switch (board_config) {
	case CXT5047_LAPTOP:
		spec->num_mixers = 2;
		spec->mixers[1] = cxt5047_hp_spk_mixers;
		codec->patch_ops.unsol_event = cxt5047_hp_unsol_event;
		break;
	case CXT5047_LAPTOP_HP:
		spec->num_mixers = 2;
		spec->mixers[1] = cxt5047_hp_only_mixers;
		codec->patch_ops.unsol_event = cxt5047_hp_unsol_event;
		codec->patch_ops.init = cxt5047_hp_init;
		break;
	case CXT5047_LAPTOP_EAPD:
		spec->input_mux = &cxt5047_toshiba_capture_source;
		spec->num_mixers = 2;
		spec->mixers[1] = cxt5047_hp_spk_mixers;
		spec->num_init_verbs = 2;
		spec->init_verbs[1] = cxt5047_toshiba_init_verbs;
		codec->patch_ops.unsol_event = cxt5047_hp_unsol_event;
		break;
#ifdef CONFIG_SND_DEBUG
	case CXT5047_TEST:
		spec->input_mux = &cxt5047_test_capture_source;
		spec->mixers[0] = cxt5047_test_mixer;
		spec->init_verbs[0] = cxt5047_test_init_verbs;
		codec->patch_ops.unsol_event = cxt5047_hp_unsol_event;
#endif	
	}
