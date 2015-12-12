switch (cmd) {
	case MTRRIOC_ADD_ENTRY:
	case MTRRIOC_SET_ENTRY:
	case MTRRIOC_DEL_ENTRY:
	case MTRRIOC_KILL_ENTRY:
	case MTRRIOC_ADD_PAGE_ENTRY:
	case MTRRIOC_SET_PAGE_ENTRY:
	case MTRRIOC_DEL_PAGE_ENTRY:
	case MTRRIOC_KILL_PAGE_ENTRY:
		if (copy_from_user(&sentry, arg, sizeof sentry))
			return -EFAULT;
		break;
	case MTRRIOC_GET_ENTRY:
	case MTRRIOC_GET_PAGE_ENTRY:
		if (copy_from_user(&gentry, arg, sizeof gentry))
			return -EFAULT;
		break;
#ifdef CONFIG_COMPAT
	case MTRRIOC32_ADD_ENTRY:
	case MTRRIOC32_SET_ENTRY:
	case MTRRIOC32_DEL_ENTRY:
	case MTRRIOC32_KILL_ENTRY:
	case MTRRIOC32_ADD_PAGE_ENTRY:
	case MTRRIOC32_SET_PAGE_ENTRY:
	case MTRRIOC32_DEL_PAGE_ENTRY:
	case MTRRIOC32_KILL_PAGE_ENTRY: {
		struct mtrr_sentry32 __user *s32;

		s32 = (struct mtrr_sentry32 __user *)__arg;
		err = get_user(sentry.base, &s32->base);
		err |= get_user(sentry.size, &s32->size);
		err |= get_user(sentry.type, &s32->type);
		if (err)
			return err;
		break;
	}
	case MTRRIOC32_GET_ENTRY:
	case MTRRIOC32_GET_PAGE_ENTRY: {
		struct mtrr_gentry32 __user *g32;

		g32 = (struct mtrr_gentry32 __user *)__arg;
		err = get_user(gentry.regnum, &g32->regnum);
		err |= get_user(gentry.base, &g32->base);
		err |= get_user(gentry.size, &g32->size);
		err |= get_user(gentry.type, &g32->type);
		if (err)
			return err;
		break;
	}
#endif
	}
