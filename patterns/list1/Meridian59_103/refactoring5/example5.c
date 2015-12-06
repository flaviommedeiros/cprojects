#ifdef _WIN32
if (fd == -2)
        if (len)
            wcstombs(state->path, path, len + 1);
        else
            *(state->path) = 0;
    else
#endif
#if !defined(NO_snprintf) && !defined(NO_vsnprintf)
        snprintf(state->path, len + 1, "%s", (const char *)path);
