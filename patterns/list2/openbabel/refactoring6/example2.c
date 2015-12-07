if ( argc == 1
#ifdef TARGET_API_LIB
        && (!inp || inp->num_atoms <= 0 || !inp->atom)
#endif        
        || argc==2 && ( argv[1][0]==INCHI_OPTION_PREFX ) &&
        (!strcmp(argv[1]+1, "?") || !stricmp(argv[1]+1, "help") ) ) {
        HelpCommandLineParms(log_file);
        out->szLog = log_file->s.pStr;
        memset( log_file, 0, sizeof(*log_file) );
        nRet = _IS_EOF;
        goto translate_RetVal;
    }
