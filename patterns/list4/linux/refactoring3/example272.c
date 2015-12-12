switch (cmd) {
	case F_SETLKW:
#ifdef F_SETLKW64
	case F_SETLKW64:
#endif
		flags = 0;
		break;
	case F_SETLK:
#ifdef F_SETLK64
	case F_SETLK64:
#endif
		flags = LDLM_FL_BLOCK_NOWAIT;
		break;
	case F_GETLK:
#ifdef F_GETLK64
	case F_GETLK64:
#endif
		flags = LDLM_FL_TEST_LOCK;
		/* Save the old mode so that if the mode in the lock changes we
		 * can decrement the appropriate reader or writer refcount. */
		file_lock->fl_type = einfo.ei_mode;
		break;
	default:
		CERROR("unknown fcntl lock command: %d\n", cmd);
		return -EINVAL;
	}
