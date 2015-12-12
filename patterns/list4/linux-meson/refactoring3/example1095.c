switch (level) {
	case PG_LEVEL_2M:
#ifdef CONFIG_X86_64
	case PG_LEVEL_1G:
#endif
		psize = page_level_size(level);
		pmask = page_level_mask(level);
		break;
	default:
		do_split = -EINVAL;
		goto out_unlock;
	}
