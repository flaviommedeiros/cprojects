switch (cmd) {
		/*
		 * Only mount owner can issue these ioctls.  Information
		 * necessary to authenticate to other NDS servers are
		 * stored here.
		 */
		case NCP_IOC_GETOBJECTNAME:
		case NCP_IOC_SETOBJECTNAME:
		case NCP_IOC_GETPRIVATEDATA:
		case NCP_IOC_SETPRIVATEDATA:
#ifdef CONFIG_COMPAT
		case NCP_IOC_GETOBJECTNAME_32:
		case NCP_IOC_SETOBJECTNAME_32:
		case NCP_IOC_GETPRIVATEDATA_32:
		case NCP_IOC_SETPRIVATEDATA_32:
#endif
			ret = -EACCES;
			goto out;
		/*
		 * These require write access on the inode if user id
		 * does not match.  Note that they do not write to the
		 * file...  But old code did mnt_want_write, so I keep
		 * it as is.  Of course not for mountpoint owner, as
		 * that breaks read-only mounts altogether as ncpmount
		 * needs working NCP_IOC_NCPREQUEST and
		 * NCP_IOC_GET_FS_INFO.  Some of these codes (setdentryttl,
		 * signinit, setsignwanted) should be probably restricted
		 * to owner only, or even more to CAP_SYS_ADMIN).
		 */
		case NCP_IOC_GET_FS_INFO:
		case NCP_IOC_GET_FS_INFO_V2:
		case NCP_IOC_NCPREQUEST:
		case NCP_IOC_SETDENTRYTTL:
		case NCP_IOC_SIGN_INIT:
		case NCP_IOC_LOCKUNLOCK:
		case NCP_IOC_SET_SIGN_WANTED:
#ifdef CONFIG_COMPAT
		case NCP_IOC_GET_FS_INFO_V2_32:
		case NCP_IOC_NCPREQUEST_32:
#endif
			ret = mnt_want_write_file(filp);
			if (ret)
				goto out;
			need_drop_write = 1;
			ret = inode_permission(inode, MAY_WRITE);
			if (ret)
				goto outDropWrite;
			break;
		/*
		 * Read access required.
		 */
		case NCP_IOC_GETMOUNTUID16:
		case NCP_IOC_GETMOUNTUID32:
		case NCP_IOC_GETMOUNTUID64:
		case NCP_IOC_GETROOT:
		case NCP_IOC_SIGN_WANTED:
			ret = inode_permission(inode, MAY_READ);
			if (ret)
				goto out;
			break;
		/*
		 * Anybody can read these.
		 */
		case NCP_IOC_GETCHARSETS:
		case NCP_IOC_GETDENTRYTTL:
		default:
		/* Three codes below are protected by CAP_SYS_ADMIN above. */
		case NCP_IOC_SETCHARSETS:
		case NCP_IOC_CONN_LOGGED_IN:
		case NCP_IOC_SETROOT:
			break;
		}
