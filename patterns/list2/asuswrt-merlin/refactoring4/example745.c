#ifdef TRU64
if ((sfs.f_type == MOUNT_NFS)||(sfs.f_type == MOUNT_NFS3))
#else /* TRU64 */
    /* XXX: make sure this really detects an nfs mounted fs */
    if (strchr(sfs.f_mntfromname, ':'))
#endif /* TRU64 */
        *nfs = 1;
