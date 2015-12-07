if ( !nStackAtom || !nRingStack || !nDfsNumber || !nLowNumber || !cNeighNumb 
#if ( FIND_RINS_SYSTEMS_DISTANCES == 1 )
        || !nRsConnect
#endif
        ) {
        nNumRingSystems = CT_OUT_OF_RAM;  /*  program error */ /*   <BRKPT> */
        goto exit_function;
    }
