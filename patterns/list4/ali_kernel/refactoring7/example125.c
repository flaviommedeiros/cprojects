return tomoyo_policy_loaded && index < TOMOYO_MAX_CONTROL_INDEX
#if TOMOYO_MAX_PROFILES != 256
		&& profile < TOMOYO_MAX_PROFILES
#endif
		&& tomoyo_profile_ptr[profile] ?
		tomoyo_profile_ptr[profile]->value[index] : 0;
