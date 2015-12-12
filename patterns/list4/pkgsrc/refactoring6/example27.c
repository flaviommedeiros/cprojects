if ((check & GF_EXCHECK) && xp > Xstring(*xs, xp)
			    && ISDIRSEP(xp[-1]) && !S_ISDIR(lstatb.st_mode)
#ifdef S_ISLNK
			    && (!S_ISLNK(lstatb.st_mode)
				|| stat_check() < 0
				|| !S_ISDIR(statb.st_mode))
#endif /* S_ISLNK */
				)
				return;
