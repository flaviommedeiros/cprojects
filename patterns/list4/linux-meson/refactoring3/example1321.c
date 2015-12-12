switch (command) {
#ifdef CONFIG_CIFS_POSIX
		case FS_IOC_GETFLAGS:
			if (pSMBFile == NULL)
				break;
			tcon = tlink_tcon(pSMBFile->tlink);
			caps = le64_to_cpu(tcon->fsUnixInfo.Capability);
			if (CIFS_UNIX_EXTATTR_CAP & caps) {
				rc = CIFSGetExtAttr(xid, tcon,
						    pSMBFile->fid.netfid,
						    &ExtAttrBits, &ExtAttrMask);
				if (rc == 0)
					rc = put_user(ExtAttrBits &
						FS_FL_USER_VISIBLE,
						(int __user *)arg);
			}
			break;

		case FS_IOC_SETFLAGS:
			if (pSMBFile == NULL)
				break;
			tcon = tlink_tcon(pSMBFile->tlink);
			caps = le64_to_cpu(tcon->fsUnixInfo.Capability);
			if (CIFS_UNIX_EXTATTR_CAP & caps) {
				if (get_user(ExtAttrBits, (int __user *)arg)) {
					rc = -EFAULT;
					break;
				}
				/*
				 * rc = CIFSGetExtAttr(xid, tcon,
				 *		       pSMBFile->fid.netfid,
				 *		       extAttrBits,
				 *		       &ExtAttrMask);
				 */
			}
			cifs_dbg(FYI, "set flags not implemented yet\n");
			break;
#endif /* CONFIG_CIFS_POSIX */
		default:
			cifs_dbg(FYI, "unsupported ioctl\n");
			break;
	}
