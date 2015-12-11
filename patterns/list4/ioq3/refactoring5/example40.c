#ifdef CUSTOM_MODES
if (coef[1] != 0)
      {
         opus_val16 coef1 = coef[1];
         opus_val16 coef3 = coef[3];
         for (j=0;j<N;j++)
         {
            celt_sig tmp = x[j] + m + VERY_SMALL;
            m = MULT16_32_Q15(coef0, tmp)
                          - MULT16_32_Q15(coef1, x[j]);
            tmp = SHL32(MULT16_32_Q15(coef3, tmp), 2);
            scratch[j] = tmp;
         }
         apply_downsampling=1;
      } else
#endif
      if (downsample>1)
      {
         /* Shortcut for the standard (non-custom modes) case */
         for (j=0;j<N;j++)
         {
            celt_sig tmp = x[j] + m + VERY_SMALL;
            m = MULT16_32_Q15(coef0, tmp);
            scratch[j] = tmp;
         }
         apply_downsampling=1;
      } else {
         /* Shortcut for the standard (non-custom modes) case */
         for (j=0;j<N;j++)
         {
            celt_sig tmp = x[j] + m + VERY_SMALL;
            m = MULT16_32_Q15(coef0, tmp);
            y[j*C] = SCALEOUT(SIG2WORD16(tmp));
         }
      }
