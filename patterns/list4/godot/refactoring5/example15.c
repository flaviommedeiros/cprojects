#ifdef CUSTOM_MODES
if (coef[1] != 0)
   {
      opus_val16 coef1 = coef[1];
      opus_val16 coef2 = coef[2];
      for (i=0;i<N;i++)
      {
         celt_sig x, tmp;
         x = inp[i];
         /* Apply pre-emphasis */
         tmp = MULT16_16(coef2, x);
         inp[i] = tmp + m;
         m = MULT16_32_Q15(coef1, inp[i]) - MULT16_32_Q15(coef0, tmp);
      }
   } else
#endif
   {
      for (i=0;i<N;i++)
      {
         celt_sig x;
         x = SHL32(inp[i], SIG_SHIFT);
         /* Apply pre-emphasis */
         inp[i] = x + m;
         m = - MULT16_32_Q15(coef0, x);
      }
   }
