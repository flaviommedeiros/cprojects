#ifdef _WIN32
if (!r && GetLastError() == ERROR_PATH_NOT_FOUND)
#else
    r = mkdir(pathname, mode);
