#if HAVE_DOS_PATHS
if ((p2.len >= 2 && p2.start[1] == ':')
        || p2.start[0] == '\\' || p2.start[0] == '/')
#else
    if (p2.start[0] == '/')
#endif
        return bstrdup0(talloc_ctx, p2);
