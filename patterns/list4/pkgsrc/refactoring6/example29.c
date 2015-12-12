if (errno != EINTR
#ifdef EEXIST
		    && errno != EEXIST
#endif /* EEXIST */
#ifdef EISDIR
		    && errno != EISDIR
#endif /* EISDIR */
			)
			/* Error must be printed by caller: don't know here if
			 * errorf() or bi_errorf() should be used.
			 */
			break;
