#if defined(RTCONFIG_CFEZ) && defined(RTCONFIG_BCMARM)
if (!chk_envrams_proc())
			return EINVAL;
