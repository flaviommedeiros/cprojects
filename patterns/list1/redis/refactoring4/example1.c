#if defined(__unix__) || defined(__unix) || defined(unix) || \
    (defined(__APPLE__) && defined(__MACH__))
if (sysctl( mib, 2, &size, &len, NULL, 0) == 0)
        return (size_t)size;
