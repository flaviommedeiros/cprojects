#if ( REL_RAC_STEREO_IGN_1_SC == 1 )
if ( !(( pINChI->nFlags & (INCHI_FLAG_REL_STEREO|INCHI_FLAG_RAC_STEREO) ) && 1 == Stereo->nNumberOfStereoCenters) )
#endif
        {
            nRet = SP3_ONLY; /*  SP3_NONE if relative stereo and 1 stereocenter */
        }
