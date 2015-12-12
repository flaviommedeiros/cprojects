#if 1
if ((attr->ia_valid & ATTR_MODE) != 0)
        {
		umode_t newmode = attr->ia_mode;

		info_mask |= DM_ATTRIBUTES;

                if (S_ISDIR(inode->i_mode)) {
                	newmode &= server->m.dir_mode;
		} else {
#ifdef CONFIG_NCPFS_EXTRAS			
			if (server->m.flags & NCP_MOUNT_EXTRAS) {
				/* any non-default execute bit set */
				if (newmode & ~server->m.file_mode & S_IXUGO)
					info.attributes |= aSHARED | aSYSTEM;
				/* read for group/world and not in default file_mode */
				else if (newmode & ~server->m.file_mode & S_IRUGO)
					info.attributes |= aSHARED;
			} else
#endif
				newmode &= server->m.file_mode;			
                }
                if (newmode & S_IWUGO)
                	info.attributes &= ~(aRONLY|aRENAMEINHIBIT|aDELETEINHIBIT);
                else
			info.attributes |=  (aRONLY|aRENAMEINHIBIT|aDELETEINHIBIT);

#ifdef CONFIG_NCPFS_NFS_NS
		if (ncp_is_nfs_extras(server, NCP_FINFO(inode)->volNumber)) {
			result = ncp_modify_nfs_info(server,
						     NCP_FINFO(inode)->volNumber,
						     NCP_FINFO(inode)->dirEntNum,
						     attr->ia_mode, 0);
			if (result != 0)
				goto out;
			info.attributes &= ~(aSHARED | aSYSTEM);
			{
				/* mark partial success */
				struct iattr tmpattr;
				
				tmpattr.ia_valid = ATTR_MODE;
				tmpattr.ia_mode = attr->ia_mode;

				setattr_copy(inode, &tmpattr);
				mark_inode_dirty(inode);
			}
		}
#endif
        }
