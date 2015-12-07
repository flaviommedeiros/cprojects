if ( argc == 1
#ifdef TARGET_API_LIB
        && (!pInp || pInp->num_atoms <= 0 || !pInp->atom)
#endif        
        || argc==2 && ( argv[1][0]==INCHI_OPTION_PREFX ) &&
        (!strcmp(argv[1]+1, "?") || !stricmp(argv[1]+1, "help") ) ) 
    {
    
        HelpCommandLineParms(log_file);
        memset( log_file, 0, sizeof(*log_file) );
        return _IS_EOF;
    }
