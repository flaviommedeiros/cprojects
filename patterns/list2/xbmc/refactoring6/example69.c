if (dsp->fdct == fdct_ifast
#ifndef FAAN_POSTSCALE
                   || dsp->fdct == ff_faandct
#endif
                   ) {
                max = (8191LL*ff_aanscales[i]) >> 14;
            }
