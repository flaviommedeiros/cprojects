#ifdef _LIBC
if (__lxstat64 (_STAT_VER, rpath, &st) < 0)
#else
          if (lstat (rpath, &st) < 0)
#endif
            goto error;
