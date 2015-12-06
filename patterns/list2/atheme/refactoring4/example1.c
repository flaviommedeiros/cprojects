#ifdef ENCRYPT_MD5
if (strcmp(buf, password) == 0)
#else
    if (0)
#endif
        return 1;
    else
        return 0;
