#if HAVE_GETFSSTAT && !defined(MFSNAMELEN)
if ((HRFS_entry->HRFS_type == MOUNT_NFS) ||
        (HRFS_entry->HRFS_type == MOUNT_AFS))
#elif defined(aix4) || defined(aix5) || defined(aix6) || defined(aix7)
    if(HRFS_entry->HRFS_type == MNT_NFS || HRFS_entry->HRFS_type == MNT_NFS3)
#else /* HAVE_GETFSSTAT */
    if ( HRFS_entry->HRFS_type != NULL && (
#if defined(MNTTYPE_NFS)
	!strcmp( HRFS_entry->HRFS_type, MNTTYPE_NFS) ||
#else
	!strcmp( HRFS_entry->HRFS_type, "nfs") ||
#endif
#if defined(MNTTYPE_NFS3)
	!strcmp( HRFS_entry->HRFS_type, MNTTYPE_NFS3) ||
#endif
#if defined(MNTTYPE_NFS4)
	!strcmp( HRFS_entry->HRFS_type, MNTTYPE_NFS4) ||
#endif
#if defined(MNTTYPE_SMBFS)
	!strcmp( HRFS_entry->HRFS_type, MNTTYPE_SMBFS) ||
#endif
#if defined(MNTTYPE_LOFS)
	!strcmp( HRFS_entry->HRFS_type, MNTTYPE_LOFS) ||
#endif
#if defined(MNTTYPE_AFP)
	!strcmp( HRFS_entry->HRFS_type, MNTTYPE_AFP) ||
#endif
	!strcmp( HRFS_entry->HRFS_type, "cifs") ||
	    /*
	     * MVFS is Rational ClearCase's view file system
	     * it is similiar to NFS file systems in that it is mounted
	     * locally or remotely from the ClearCase server
	     */
	!strcmp( HRFS_entry->HRFS_type, "mvfs")))
#endif /* HAVE_GETFSSTAT */
	return 1;
