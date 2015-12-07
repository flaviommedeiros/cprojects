if ( (ip->bINChIOutputOptions & INCHI_OUT_XML)
#ifdef TARGET_LIB_FOR_WINCHI
         || (ip->bINChIOutputOptions & INCHI_OUT_WINCHI_WINDOW) && (ip->bINChIOutputOptions & INCHI_OUT_PLAIN_TEXT)
#endif
        ) {
        if ( sd->nErrorType != _IS_OKAY && sd->nErrorType != _IS_WARNING ) {
            sd->nErrorType =
                ProcessStructError( output_file, log_file, /*sd->nStructReadError,*/
                         sd->pStrErrStruct, sd->nErrorType, &sd->bXmlStructStarted, *num_inp, ip, pStr, nStrLen );
        }
    }
