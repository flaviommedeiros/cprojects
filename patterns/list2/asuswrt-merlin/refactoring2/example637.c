#if ENABLE_FEATURE_UTMP
if (getlogin_r(user_buf, sizeof(user_buf)) != 0)
#endif
		{
			pw = getpwuid(cur_uid);
			old_user = pw ? xstrdup(pw->pw_name) : "";
		}
