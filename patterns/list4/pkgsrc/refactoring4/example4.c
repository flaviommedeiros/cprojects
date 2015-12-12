#ifdef NO_GETPW_R
if ((pwd = getpwuid(getuid())) == NULL)
#else
			if (getpwuid_r(getuid(), &pwres, pwbuf, sizeof(pwbuf),
			    &pwd) != 0 || pwd == NULL)
#endif
				return pattern;
			else
				h = pwd->pw_dir;
