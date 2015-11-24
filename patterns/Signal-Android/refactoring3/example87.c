switch(request)
   {
   case SPEEX_GET_FRAME_SIZE:
      (*(spx_int32_t*)ptr) = st->full_frame_size;
      break;
   case SPEEX_SET_HIGH_MODE:
      st->submodeSelect = st->submodeID = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_SET_LOW_MODE:
      speex_encoder_ctl(st->st_low, SPEEX_SET_LOW_MODE, ptr);
      break;
   case SPEEX_SET_DTX:
      speex_encoder_ctl(st->st_low, SPEEX_SET_DTX, ptr);
      break;
   case SPEEX_GET_DTX:
      speex_encoder_ctl(st->st_low, SPEEX_GET_DTX, ptr);
      break;
   case SPEEX_GET_LOW_MODE:
      speex_encoder_ctl(st->st_low, SPEEX_GET_LOW_MODE, ptr);
      break;
   case SPEEX_SET_MODE:
      speex_encoder_ctl(st, SPEEX_SET_QUALITY, ptr);
      break;
#ifndef DISABLE_VBR
   case SPEEX_SET_VBR:
      st->vbr_enabled = (*(spx_int32_t*)ptr);
      speex_encoder_ctl(st->st_low, SPEEX_SET_VBR, ptr);
      break;
   case SPEEX_GET_VBR:
      (*(spx_int32_t*)ptr) = st->vbr_enabled;
      break;
   case SPEEX_SET_VAD:
      st->vad_enabled = (*(spx_int32_t*)ptr);
      speex_encoder_ctl(st->st_low, SPEEX_SET_VAD, ptr);
      break;
   case SPEEX_GET_VAD:
      (*(spx_int32_t*)ptr) = st->vad_enabled;
      break;
#endif /* #ifndef DISABLE_VBR */
#if !defined(DISABLE_VBR) && !defined(DISABLE_FLOAT_API)
   case SPEEX_SET_VBR_QUALITY:
      {
         spx_int32_t q;
         float qual = (*(float*)ptr)+.6;
         st->vbr_quality = (*(float*)ptr);
         if (qual>10)
            qual=10;
         q=(int)floor(.5+*(float*)ptr);
         if (q>10)
            q=10;
         speex_encoder_ctl(st->st_low, SPEEX_SET_VBR_QUALITY, &qual);
         speex_encoder_ctl(state, SPEEX_SET_QUALITY, &q);
         break;
      }
   case SPEEX_GET_VBR_QUALITY:
      (*(float*)ptr) = st->vbr_quality;
      break;
#endif /* #if !defined(DISABLE_VBR) && !defined(DISABLE_FLOAT_API) */
#ifndef DISABLE_VBR
   case SPEEX_SET_ABR:
      st->abr_enabled = (*(spx_int32_t*)ptr);
      st->vbr_enabled = st->abr_enabled!=0;
      speex_encoder_ctl(st->st_low, SPEEX_SET_VBR, &st->vbr_enabled);
      if (st->vbr_enabled) 
      {
         spx_int32_t i=10, rate, target;
         float vbr_qual;
         target = (*(spx_int32_t*)ptr);
         while (i>=0)
         {
            speex_encoder_ctl(st, SPEEX_SET_QUALITY, &i);
            speex_encoder_ctl(st, SPEEX_GET_BITRATE, &rate);
            if (rate <= target)
               break;
            i--;
         }
         vbr_qual=i;
         if (vbr_qual<0)
            vbr_qual=0;
         speex_encoder_ctl(st, SPEEX_SET_VBR_QUALITY, &vbr_qual);
         st->abr_count=0;
         st->abr_drift=0;
         st->abr_drift2=0;
      }
      
      break;
   case SPEEX_GET_ABR:
      (*(spx_int32_t*)ptr) = st->abr_enabled;
      break;
#endif /* #ifndef DISABLE_VBR */

   case SPEEX_SET_QUALITY:
      {
         spx_int32_t nb_qual;
         int quality = (*(spx_int32_t*)ptr);
         if (quality < 0)
            quality = 0;
         if (quality > 10)
            quality = 10;
         st->submodeSelect = st->submodeID = ((const SpeexSBMode*)(st->mode->mode))->quality_map[quality];
         nb_qual = ((const SpeexSBMode*)(st->mode->mode))->low_quality_map[quality];
         speex_encoder_ctl(st->st_low, SPEEX_SET_MODE, &nb_qual);
      }
      break;
   case SPEEX_SET_COMPLEXITY:
      speex_encoder_ctl(st->st_low, SPEEX_SET_COMPLEXITY, ptr);
      st->complexity = (*(spx_int32_t*)ptr);
      if (st->complexity<1)
         st->complexity=1;
      break;
   case SPEEX_GET_COMPLEXITY:
      (*(spx_int32_t*)ptr) = st->complexity;
      break;
   case SPEEX_SET_BITRATE:
      {
         spx_int32_t i=10;
         spx_int32_t rate, target;
         target = (*(spx_int32_t*)ptr);
         while (i>=0)
         {
            speex_encoder_ctl(st, SPEEX_SET_QUALITY, &i);
            speex_encoder_ctl(st, SPEEX_GET_BITRATE, &rate);
            if (rate <= target)
               break;
            i--;
         }
      }
      break;
   case SPEEX_GET_BITRATE:
      speex_encoder_ctl(st->st_low, request, ptr);
      /*fprintf (stderr, "before: %d\n", (*(int*)ptr));*/
      if (st->submodes[st->submodeID])
         (*(spx_int32_t*)ptr) += st->sampling_rate*SUBMODE(bits_per_frame)/st->full_frame_size;
      else
         (*(spx_int32_t*)ptr) += st->sampling_rate*(SB_SUBMODE_BITS+1)/st->full_frame_size;
      /*fprintf (stderr, "after: %d\n", (*(int*)ptr));*/
      break;
   case SPEEX_SET_SAMPLING_RATE:
      {
         spx_int32_t tmp=(*(spx_int32_t*)ptr);
         st->sampling_rate = tmp;
         tmp>>=1;
         speex_encoder_ctl(st->st_low, SPEEX_SET_SAMPLING_RATE, &tmp);
      }
      break;
   case SPEEX_GET_SAMPLING_RATE:
      (*(spx_int32_t*)ptr)=st->sampling_rate;
      break;
   case SPEEX_RESET_STATE:
      {
         int i;
         st->first = 1;
         for (i=0;i<st->lpcSize;i++)
            st->old_lsp[i]= DIV32(MULT16_16(QCONST16(3.1415927f, LSP_SHIFT), i+1), st->lpcSize+1);
         for (i=0;i<st->lpcSize;i++)
            st->mem_sw[i]=st->mem_sp[i]=st->mem_sp2[i]=0;
         for (i=0;i<QMF_ORDER;i++)
            st->h0_mem[i]=st->h1_mem[i]=0;
      }
      break;
   case SPEEX_SET_SUBMODE_ENCODING:
      st->encode_submode = (*(spx_int32_t*)ptr);
      speex_encoder_ctl(st->st_low, SPEEX_SET_SUBMODE_ENCODING, ptr);
      break;
   case SPEEX_GET_SUBMODE_ENCODING:
      (*(spx_int32_t*)ptr) = st->encode_submode;
      break;
   case SPEEX_GET_LOOKAHEAD:
      speex_encoder_ctl(st->st_low, SPEEX_GET_LOOKAHEAD, ptr);
      (*(spx_int32_t*)ptr) = 2*(*(spx_int32_t*)ptr) + QMF_ORDER - 1;
      break;
   case SPEEX_SET_PLC_TUNING:
      speex_encoder_ctl(st->st_low, SPEEX_SET_PLC_TUNING, ptr);
      break;
   case SPEEX_GET_PLC_TUNING:
      speex_encoder_ctl(st->st_low, SPEEX_GET_PLC_TUNING, ptr);
      break;
#ifndef DISABLE_VBR
   case SPEEX_SET_VBR_MAX_BITRATE:
      {
         st->vbr_max = (*(spx_int32_t*)ptr);
         if (SPEEX_SET_VBR_MAX_BITRATE<1)
         {
            speex_encoder_ctl(st->st_low, SPEEX_SET_VBR_MAX_BITRATE, &st->vbr_max);
            st->vbr_max_high = 17600;
         } else {
            spx_int32_t low_rate;
            if (st->vbr_max >= 42200)
            {
               st->vbr_max_high = 17600;
            } else if (st->vbr_max >= 27800)
            {
               st->vbr_max_high = 9600;
            } else if (st->vbr_max > 20600)
            {
               st->vbr_max_high = 5600;
            } else {
               st->vbr_max_high = 1800;
            }
            if (st->subframeSize==80)
               st->vbr_max_high = 1800;
            low_rate = st->vbr_max - st->vbr_max_high;
            speex_encoder_ctl(st->st_low, SPEEX_SET_VBR_MAX_BITRATE, &low_rate);
         }
      }
      break;
   case SPEEX_GET_VBR_MAX_BITRATE:
      (*(spx_int32_t*)ptr) = st->vbr_max;
      break;
#endif /* #ifndef DISABLE_VBR */
   case SPEEX_SET_HIGHPASS:
      speex_encoder_ctl(st->st_low, SPEEX_SET_HIGHPASS, ptr);
      break;
   case SPEEX_GET_HIGHPASS:
      speex_encoder_ctl(st->st_low, SPEEX_GET_HIGHPASS, ptr);
      break;


   /* This is all internal stuff past this point */
   case SPEEX_GET_PI_GAIN:
      {
         int i;
         spx_word32_t *g = (spx_word32_t*)ptr;
         for (i=0;i<st->nbSubframes;i++)
            g[i]=st->pi_gain[i];
      }
      break;
   case SPEEX_GET_EXC:
      {
         int i;
         for (i=0;i<st->nbSubframes;i++)
            ((spx_word16_t*)ptr)[i] = st->exc_rms[i];
      }
      break;
#ifndef DISABLE_VBR
   case SPEEX_GET_RELATIVE_QUALITY:
      (*(float*)ptr)=st->relative_quality;
      break;
#endif /* #ifndef DISABLE_VBR */
   case SPEEX_SET_INNOVATION_SAVE:
      st->innov_rms_save = (spx_word16_t*)ptr;
      break;
   case SPEEX_SET_WIDEBAND:
      speex_encoder_ctl(st->st_low, SPEEX_SET_WIDEBAND, ptr);
      break;
   case SPEEX_GET_STACK:
      *((char**)ptr) = st->stack;
      break;
   default:
      speex_warning_int("Unknown nb_ctl request: ", request);
      return -1;
   }
