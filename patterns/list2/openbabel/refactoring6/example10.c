if ( Stereo1 && ( Stereo1->nNumberOfStereoBonds > 0 || 
                      Stereo1->nNumberOfStereoCenters > 0
#if ( REL_RAC_STEREO_IGN_1_SC == 1 )
                      && /*  do not compare single stereocenters in case of relative stereo */
                      !((nFlags1 & (INCHI_FLAG_REL_STEREO|INCHI_FLAG_RAC_STEREO)) &&
                       1 == Stereo1->nNumberOfStereoCenters
                       )
#endif
       ) ) {
        return -1;
    }
