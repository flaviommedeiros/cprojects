switch (xprefix) {
	case JFFS2_XPREFIX_USER:
		ret = &jffs2_user_xattr_handler;
		break;
#ifdef CONFIG_JFFS2_FS_SECURITY
	case JFFS2_XPREFIX_SECURITY:
		ret = &jffs2_security_xattr_handler;
		break;
#endif
#ifdef CONFIG_JFFS2_FS_POSIX_ACL
	case JFFS2_XPREFIX_ACL_ACCESS:
		ret = &posix_acl_access_xattr_handler;
		break;
	case JFFS2_XPREFIX_ACL_DEFAULT:
		ret = &posix_acl_default_xattr_handler;
		break;
#endif
	case JFFS2_XPREFIX_TRUSTED:
		ret = &jffs2_trusted_xattr_handler;
		break;
	default:
		ret = NULL;
		break;
	}
