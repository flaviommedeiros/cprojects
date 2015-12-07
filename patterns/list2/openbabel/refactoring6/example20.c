if ( (ip->bINChIOutputOptions & INCHI_OUT_XML)
#ifdef TARGET_LIB_FOR_WINCHI
             || (ip->bINChIOutputOptions & INCHI_OUT_WINCHI_WINDOW) && (ip->bINChIOutputOptions & INCHI_OUT_PLAIN_TEXT)
#endif
            ) {
            sd->nErrorType = ProcessStructError( output_file, log_file, /*sd->nErrorCode,*/ sd->pStrErrStruct,
                                            sd->nErrorType, &sd->bXmlStructStarted, num_inp, ip, pStr, nStrLen );
            /*  save the problem structure */
            if ( prb_file->f && 0L <= sd->fPtrStart && sd->fPtrStart < sd->fPtrEnd && !ip->bSaveAllGoodStructsAsProblem ) {
                CopyMOLfile(inp_file->f, sd->fPtrStart, sd->fPtrEnd, prb_file->f, num_inp);
            }
        } else {
            /*  save the problem structure */
            if ( sd->nErrorCode && prb_file->f && 0L <= sd->fPtrStart && sd->fPtrStart < sd->fPtrEnd && !ip->bSaveAllGoodStructsAsProblem ) {
                CopyMOLfile(inp_file->f, sd->fPtrStart, sd->fPtrEnd, prb_file->f, num_inp);
            }
        }
