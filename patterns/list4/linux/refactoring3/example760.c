switch (compr) {
	case JFFS2_COMPR_MODE_NONE:
		return "none";
#ifdef CONFIG_JFFS2_LZO
	case JFFS2_COMPR_MODE_FORCELZO:
		return "lzo";
#endif
#ifdef CONFIG_JFFS2_ZLIB
	case JFFS2_COMPR_MODE_FORCEZLIB:
		return "zlib";
#endif
	default:
		/* should never happen; programmer error */
		WARN_ON(1);
		return "";
	}
