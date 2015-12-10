#if DUMP_DIR_OWNED_BY_USER > 0
if (uid == dd->dd_uid)
#else
    if (uid_in_group(uid, dd->dd_gid))
#endif
    {
        log_debug("fs attributes: %ld uid owns directory", (long)uid);
        ddstat |= DD_OWNER_FLAGS;
    }
