switch (ic->class) {
#ifdef CONFIG_JFFS2_FS_XATTR
		case RAWNODE_CLASS_XATTR_DATUM:
			jffs2_release_xattr_datum(c, (struct jffs2_xattr_datum *)ic);
			break;
		case RAWNODE_CLASS_XATTR_REF:
			jffs2_release_xattr_ref(c, (struct jffs2_xattr_ref *)ic);
			break;
#endif
		default:
			if (ic->nodes == (void *)ic && ic->pino_nlink == 0)
				jffs2_del_ino_cache(c, ic);
	}
