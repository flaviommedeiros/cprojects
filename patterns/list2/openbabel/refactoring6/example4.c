if ( argc == 1
#ifdef TARGET_API_LIB
        && (!inpInChI || !inpInChI->szInChI)
#endif        
        || argc==2 && ( argv[1][0]==INCHI_OPTION_PREFX ) &&
        (!strcmp(argv[1]+1, "?") || !stricmp(argv[1]+1, "help") ) ) {
        HelpCommandLineParms(log_file);
        outStruct->szLog = log_file->s.pStr;
        nRet = _IS_EOF;
        goto translate_RetVal;
    }
