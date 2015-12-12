switch (command) {
		case CIFS_IOC_CHECKUMOUNT:
			cFYI(1, "User unmount attempted");
			if (cifs_sb->mnt_uid == current_uid())
				rc = 0;
			else {
				rc = -EACCES;
				cFYI(1, "uids do not match");
			}
			break;
#ifdef CONFIG_CIFS_POSIX
		case FS_IOC_GETFLAGS:
			if (pSMBFile == NULL)
				break;
			tcon = tlink_tcon(pSMBFile->tlink);
			caps = le64_to_cpu(tcon->fsUnixInfo.Capability);
			if (CIFS_UNIX_EXTATTR_CAP & caps) {
				rc = CIFSGetExtAttr(xid, tcon, pSMBFile->netfid,
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
				/* rc= CIFSGetExtAttr(xid,tcon,pSMBFile->netfid,
					extAttrBits, &ExtAttrMask);*/
			}
			cFYI(1, "set flags not implemented yet");
			break;
#endif /* CONFIG_CIFS_POSIX */
		default:
			cFYI(1, "unsupported ioctl");
			break;
	}
