#ifdef OPUS_FIXED_POINT
if (!(S1 > SHR32(S2,2)))
#else
            /* The float test is written this way to catch NaNs in the output
               of the IIR filter at the same time. */
            if (!(S1 > 0.2f*S2))
#endif
            {
               for (i=0;i<extrapolation_len;i++)
                  buf[DECODE_BUFFER_SIZE-N+i] = 0;
            } else if (S1 < S2)
            {
               opus_val16 ratio = celt_sqrt(frac_div32(SHR32(S1,1)+1,S2+1));
               for (i=0;i<overlap;i++)
               {
                  opus_val16 tmp_g = Q15ONE
                        - MULT16_16_Q15(window[i], Q15ONE-ratio);
                  buf[DECODE_BUFFER_SIZE-N+i] =
                        MULT16_32_Q15(tmp_g, buf[DECODE_BUFFER_SIZE-N+i]);
               }
               for (i=overlap;i<extrapolation_len;i++)
               {
                  buf[DECODE_BUFFER_SIZE-N+i] =
                        MULT16_32_Q15(ratio, buf[DECODE_BUFFER_SIZE-N+i]);
               }
            }
