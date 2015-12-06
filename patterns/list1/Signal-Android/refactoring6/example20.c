if (!st->submodes[st->submodeID] || (st->complexity>2 && SUBMODE(have_subframe_gain)<3) || SUBMODE(forced_pitch_gain) || SUBMODE(lbr_pitch) != -1 
#ifndef DISABLE_VBR
           || st->vbr_enabled || st->vad_enabled
#endif
                  )
      {
         int nol_pitch[6];
         spx_word16_t nol_pitch_coef[6];
         
         bw_lpc(st->gamma1, interp_lpc, bw_lpc1, st->lpcSize);
         bw_lpc(st->gamma2, interp_lpc, bw_lpc2, st->lpcSize);

         SPEEX_COPY(st->sw, st->winBuf, diff);
         SPEEX_COPY(st->sw+diff, in, st->frameSize-diff);
         filter_mem16(st->sw, bw_lpc1, bw_lpc2, st->sw, st->frameSize, st->lpcSize, st->mem_sw_whole, stack);

         open_loop_nbest_pitch(st->sw, st->min_pitch, st->max_pitch, st->frameSize, 
                               nol_pitch, nol_pitch_coef, 6, stack);
         ol_pitch=nol_pitch[0];
         ol_pitch_coef = nol_pitch_coef[0];
         /*Try to remove pitch multiples*/
         for (i=1;i<6;i++)
         {
#ifdef FIXED_POINT
            if ((nol_pitch_coef[i]>MULT16_16_Q15(nol_pitch_coef[0],27853)) && 
#else
            if ((nol_pitch_coef[i]>.85*nol_pitch_coef[0]) && 
#endif
                (ABS(2*nol_pitch[i]-ol_pitch)<=2 || ABS(3*nol_pitch[i]-ol_pitch)<=3 || 
                 ABS(4*nol_pitch[i]-ol_pitch)<=4 || ABS(5*nol_pitch[i]-ol_pitch)<=5))
            {
               /*ol_pitch_coef=nol_pitch_coef[i];*/
               ol_pitch = nol_pitch[i];
            }
         }
         /*if (ol_pitch>50)
           ol_pitch/=2;*/
         /*ol_pitch_coef = sqrt(ol_pitch_coef);*/

      } else {
         ol_pitch=0;
         ol_pitch_coef=0;
      }
