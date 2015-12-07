#if HAVE_HASMNTOPT
if (hasmntopt( m, "ro" ))
            entry->flags |= NETSNMP_FS_FLAG_RONLY;
