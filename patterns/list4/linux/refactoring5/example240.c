#ifdef CONFIG_CIFS_ACL
if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_ACL) {
		if (uid_valid(uid) || gid_valid(gid)) {
			rc = id_mode_to_cifs_acl(inode, full_path, NO_CHANGE_64,
							uid, gid);
			if (rc) {
				cifs_dbg(FYI, "%s: Setting id failed with error: %d\n",
					 __func__, rc);
				goto cifs_setattr_exit;
			}
		}
	} else
#endif /* CONFIG_CIFS_ACL */
	if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SET_UID))
		attrs->ia_valid &= ~(ATTR_UID | ATTR_GID);
