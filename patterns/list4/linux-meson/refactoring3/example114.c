switch (cmd) {
	/*
	 * these need special handlers for incompatible data structures
	 */
	case PIO_FONTX:
	case GIO_FONTX:
		ret = compat_fontx_ioctl(cmd, up, perm, &op);
		break;

	case KDFONTOP:
		ret = compat_kdfontop_ioctl(up, perm, &op, vc);
		break;

	case PIO_UNIMAP:
	case GIO_UNIMAP:
		ret = compat_unimap_ioctl(cmd, up, perm, vc);
		break;

	/*
	 * all these treat 'arg' as an integer
	 */
	case KIOCSOUND:
	case KDMKTONE:
#ifdef CONFIG_X86
	case KDADDIO:
	case KDDELIO:
#endif
	case KDSETMODE:
	case KDMAPDISP:
	case KDUNMAPDISP:
	case KDSKBMODE:
	case KDSKBMETA:
	case KDSKBLED:
	case KDSETLED:
	case KDSIGACCEPT:
	case VT_ACTIVATE:
	case VT_WAITACTIVE:
	case VT_RELDISP:
	case VT_DISALLOCATE:
	case VT_RESIZE:
	case VT_RESIZEX:
		goto fallback;

	/*
	 * the rest has a compatible data structure behind arg,
	 * but we have to convert it to a proper 64 bit pointer.
	 */
	default:
		arg = (unsigned long)compat_ptr(arg);
		goto fallback;
	}
