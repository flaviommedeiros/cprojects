#ifdef _WIN32
if ( !stricmp(str, keysym_names[nn]._str) )
#else
        if ( !strcasecmp(str, keysym_names[nn]._str) )
#endif
        {
            *psym = keysym_names[nn]._sym;
            *pmod = mod;
            return 0;
        }
