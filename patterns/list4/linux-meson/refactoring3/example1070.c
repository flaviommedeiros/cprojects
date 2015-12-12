switch (cmd) {
	case MTRRIOC_GET_ENTRY:
	case MTRRIOC_GET_PAGE_ENTRY:
		if (copy_to_user(arg, &gentry, sizeof gentry))
			err = -EFAULT;
		break;
#ifdef CONFIG_COMPAT
	case MTRRIOC32_GET_ENTRY:
	case MTRRIOC32_GET_PAGE_ENTRY: {
		struct mtrr_gentry32 __user *g32;

		g32 = (struct mtrr_gentry32 __user *)__arg;
		err = put_user(gentry.base, &g32->base);
		err |= put_user(gentry.size, &g32->size);
		err |= put_user(gentry.regnum, &g32->regnum);
		err |= put_user(gentry.type, &g32->type);
		break;
	}
#endif
	}
