if (   s->dsp.fdct == fdct_ifast
#ifndef FAAN_POSTSCALE
            || s->dsp.fdct == ff_faandct
#endif
           )
            dct_coeff= (dct_coeff*ff_inv_aanscales[ scantable[i] ]) >> 12;
