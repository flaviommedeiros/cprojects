switch (cmd) {
	default:
		return -ENOTTY;
	case MTRRIOC_ADD_ENTRY:
#ifdef CONFIG_COMPAT
	case MTRRIOC32_ADD_ENTRY:
#endif
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		err =
		    mtrr_file_add(sentry.base, sentry.size, sentry.type, true,
				  file, 0);
		break;
	case MTRRIOC_SET_ENTRY:
#ifdef CONFIG_COMPAT
	case MTRRIOC32_SET_ENTRY:
#endif
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		err = mtrr_add(sentry.base, sentry.size, sentry.type, false);
		break;
	case MTRRIOC_DEL_ENTRY:
#ifdef CONFIG_COMPAT
	case MTRRIOC32_DEL_ENTRY:
#endif
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		err = mtrr_file_del(sentry.base, sentry.size, file, 0);
		break;
	case MTRRIOC_KILL_ENTRY:
#ifdef CONFIG_COMPAT
	case MTRRIOC32_KILL_ENTRY:
#endif
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		err = mtrr_del(-1, sentry.base, sentry.size);
		break;
	case MTRRIOC_GET_ENTRY:
#ifdef CONFIG_COMPAT
	case MTRRIOC32_GET_ENTRY:
#endif
		if (gentry.regnum >= num_var_ranges)
			return -EINVAL;
		mtrr_if->get(gentry.regnum, &gentry.base, &size, &type);

		/* Hide entries that go above 4GB */
		if (gentry.base + size - 1 >= (1UL << (8 * sizeof(gentry.size) - PAGE_SHIFT))
		    || size >= (1UL << (8 * sizeof(gentry.size) - PAGE_SHIFT)))
			gentry.base = gentry.size = gentry.type = 0;
		else {
			gentry.base <<= PAGE_SHIFT;
			gentry.size = size << PAGE_SHIFT;
			gentry.type = type;
		}

		break;
	case MTRRIOC_ADD_PAGE_ENTRY:
#ifdef CONFIG_COMPAT
	case MTRRIOC32_ADD_PAGE_ENTRY:
#endif
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		err =
		    mtrr_file_add(sentry.base, sentry.size, sentry.type, true,
				  file, 1);
		break;
	case MTRRIOC_SET_PAGE_ENTRY:
#ifdef CONFIG_COMPAT
	case MTRRIOC32_SET_PAGE_ENTRY:
#endif
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		err =
		    mtrr_add_page(sentry.base, sentry.size, sentry.type, false);
		break;
	case MTRRIOC_DEL_PAGE_ENTRY:
#ifdef CONFIG_COMPAT
	case MTRRIOC32_DEL_PAGE_ENTRY:
#endif
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		err = mtrr_file_del(sentry.base, sentry.size, file, 1);
		break;
	case MTRRIOC_KILL_PAGE_ENTRY:
#ifdef CONFIG_COMPAT
	case MTRRIOC32_KILL_PAGE_ENTRY:
#endif
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		err = mtrr_del_page(-1, sentry.base, sentry.size);
		break;
	case MTRRIOC_GET_PAGE_ENTRY:
#ifdef CONFIG_COMPAT
	case MTRRIOC32_GET_PAGE_ENTRY:
#endif
		if (gentry.regnum >= num_var_ranges)
			return -EINVAL;
		mtrr_if->get(gentry.regnum, &gentry.base, &size, &type);
		/* Hide entries that would overflow */
		if (size != (__typeof__(gentry.size))size)
			gentry.base = gentry.size = gentry.type = 0;
		else {
			gentry.size = size;
			gentry.type = type;
		}
		break;
	}
