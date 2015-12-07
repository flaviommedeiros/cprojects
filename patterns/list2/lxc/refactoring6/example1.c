if (seccomp_attr_set(
#if HAVE_SCMP_FILTER_CTX
			conf->seccomp_ctx,
#endif
			SCMP_FLTATR_CTL_NNP, 0)) {
		ERROR("failed to turn off n-new-privs");
		return -1;
	}
