#ifndef NILFS_ATIME_DISABLE
if (flags & NILFS_NOATIME_FL)
#endif
		inode->i_flags |= S_NOATIME;
