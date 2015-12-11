#ifdef NO_GETPW_R
if ((pwd = getpwnam(d)) == NULL)
#else
		if (getpwnam_r(d, &pwres, pwbuf, sizeof(pwbuf), &pwd) != 0 ||
		    pwd == NULL)
#endif
			return pattern;
		else
			h = pwd->pw_dir;
