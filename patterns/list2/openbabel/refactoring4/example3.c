#ifdef TARGET_LIB_FOR_WINCHI
if ( ip->bDisplay && bINCHI_LIB_Flag )
#else
    if ( (ip->bDisplay || (ip->bCompareComponents & CMP_COMPONENTS)) && bINCHI_LIB_Flag )
#endif
    {
        int bBit, k, bReconnected, nComponent, bPreprocessed;
        for ( bBit = 1, k = 0; k < 8; k ++, bBit <<= 1 ) {
            /******************************************************************************
             *  bReconnected  = k%2     (0 or 1)
             *  nComponent    = k/4     (0 or 1)
             *  bPreprocessed = (k/2)%2 (0 or 1)
             ******************************************************************************/
            if ( !(bINCHI_LIB_Flag & bBit) ) {
                continue;
            }
            bReconnected  = k%2;
            nComponent    = k/4;
            bPreprocessed = ((k/2)%2);

            sprintf( szTitle, "%s Structure #%ld.%s%s%s%s",
                              bPreprocessed? "Preprocessed" : bReconnected? "Reconnected" : "Input",
                              num_inp,
                              SDF_LBL_VAL(ip->pSdfLabel,ip->pSdfValue));

#ifdef TARGET_LIB_FOR_WINCHI
            if(DRAWDATA && DRAWDATA_EXISTS)
            {
                struct DrawData vDrawData;
                int    nType = bPreprocessed? COMPONENT_ORIGINAL_PREPROCESSED : COMPONENT_ORIGINAL;
                if ( DRAWDATA_EXISTS( nComponent, bPreprocessed, bReconnected ) ) {
                    sd->nErrorType = _IS_FATAL;
                    sd->nErrorCode = CT_UNKNOWN_ERR;
                    return -1;
                }
                vDrawData.pWindowData = CreateWinData_( orig_inp_data->at, orig_inp_data->num_inp_atoms,
                                                        0, 1 /* bAdd_DT_to_num_H */, 0, NULL, 1, 0, NULL, NULL,
                                                        ip->bAbcNumbers, &ip->dp, ip->nMode );
                if( vDrawData.pWindowData != NULL )
                {
                    vDrawData.nComponent   = nComponent;
                    vDrawData.nType        = nType; /* COMPONENT_ORIGINAL or COMPONENT_ORIGINAL_PREPROCESSED */
                    vDrawData.bReconnected = bReconnected; /* 0=>main; 1=>reconnected */
                    vDrawData.pWindowData->szTitle = _strdup(szTitle);
                    vDrawData.szTitle              = _strdup(szTitle);
                    DRAWDATA(&vDrawData);
                    if ( !nComponent ) {
                        /* keep track of saved INCHI_LIB data */
                        orig_inp_data->bSavedInINCHI_LIB[bReconnected] ++;
                        orig_inp_data->bPreprocessed[bReconnected]    = bPreprocessed;
                    }
                }
            }
#else
            if ( !nComponent ) {
                /* keep track of saved INCHI_LIB data */
                orig_inp_data->bSavedInINCHI_LIB[bReconnected] ++;
                orig_inp_data->bPreprocessed[bReconnected]    = bPreprocessed;
            }
#endif

        }
    }
