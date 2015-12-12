#ifdef XFS_NATIVE_HOST
if (ip->i_d.di_nextents == ip->i_df.if_bytes /
                                               (uint)sizeof(xfs_bmbt_rec_t)) {
				/*
				 * There are no delayed allocation
				 * extents, so just point to the
				 * real extents array.
				 */
				vecp->i_addr = ip->i_df.if_u1.if_extents;
				vecp->i_len = ip->i_df.if_bytes;
				vecp->i_type = XLOG_REG_TYPE_IEXT;
			} else
#endif
			{
				xfs_inode_item_format_extents(ip, vecp,
					XFS_DATA_FORK, XLOG_REG_TYPE_IEXT);
			}
