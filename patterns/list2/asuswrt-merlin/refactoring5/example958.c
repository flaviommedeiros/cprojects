#ifdef XFS_NATIVE_HOST
if (nrecs == ip->i_d.di_nextents) {
				/*
				 * There are no delayed allocation
				 * extents, so just point to the
				 * real extents array.
				 */
				vecp->i_addr =
					(char *)(ip->i_df.if_u1.if_extents);
				vecp->i_len = ip->i_df.if_bytes;
				XLOG_VEC_SET_TYPE(vecp, XLOG_REG_TYPE_IEXT);
			} else
#endif
			{
				/*
				 * There are delayed allocation extents
				 * in the inode, or we need to convert
				 * the extents to on disk format.
				 * Use xfs_iextents_copy()
				 * to copy only the real extents into
				 * a separate buffer.  We'll free the
				 * buffer in the unlock routine.
				 */
				ext_buffer = kmem_alloc(ip->i_df.if_bytes,
					KM_SLEEP);
				iip->ili_extents_buf = ext_buffer;
				vecp->i_addr = (xfs_caddr_t)ext_buffer;
				vecp->i_len = xfs_iextents_copy(ip, ext_buffer,
						XFS_DATA_FORK);
				XLOG_VEC_SET_TYPE(vecp, XLOG_REG_TYPE_IEXT);
			}
