switch (inst->method) {
	case AUTH_INTERNAL:
		DEBUG("rlm_mschap (%s): using internal authentication", inst->xlat_name);
		break;
	case AUTH_NTLMAUTH_EXEC:
		DEBUG("rlm_mschap (%s): authenticating by calling 'ntlm_auth'", inst->xlat_name);
		break;
#ifdef WITH_AUTH_WINBIND
	case AUTH_WBCLIENT:
		DEBUG("rlm_mschap (%s): authenticating directly to winbind", inst->xlat_name);
		break;
#endif
	}
