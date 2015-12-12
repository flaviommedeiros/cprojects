#ifdef CONFIG_CIFS_ACL
if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_ACL) {
		if (uid != NO_CHANGE_32 || gid != NO_CHANGE_32) {
			rc = id_mode_to_cifs_acl(inode, full_path, NO_CHANGE_64,
							uid, gid);
			if (rc) {
				cFYI(1, "%s: Setting id failed with error: %d",
					__func__, rc);
				goto cifs_setattr_exit;
			}
		}
	} else
#endif /* CONFIG_CIFS_ACL */
	if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SET_UID))
		attrs->ia_valid &= ~(ATTR_UID | ATTR_GID);
