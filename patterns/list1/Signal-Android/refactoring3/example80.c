switch(request)
   {
   case SPEEX_GET_FRAME_SIZE:
      (*(spx_int32_t*)ptr) = st->frameSize;
      break;
   case SPEEX_SET_LOW_MODE:
   case SPEEX_SET_MODE:
      st->submodeSelect = st->submodeID = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_GET_LOW_MODE:
   case SPEEX_GET_MODE:
      (*(spx_int32_t*)ptr) = st->submodeID;
      break;
#ifndef DISABLE_VBR
      case SPEEX_SET_VBR:
      st->vbr_enabled = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_GET_VBR:
      (*(spx_int32_t*)ptr) = st->vbr_enabled;
      break;
   case SPEEX_SET_VAD:
      st->vad_enabled = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_GET_VAD:
      (*(spx_int32_t*)ptr) = st->vad_enabled;
      break;
   case SPEEX_SET_DTX:
      st->dtx_enabled = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_GET_DTX:
      (*(spx_int32_t*)ptr) = st->dtx_enabled;
      break;
   case SPEEX_SET_ABR:
      st->abr_enabled = (*(spx_int32_t*)ptr);
      st->vbr_enabled = st->abr_enabled!=0;
      if (st->vbr_enabled) 
      {
         spx_int32_t i=10;
         spx_int32_t rate, target;
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
#if !defined(DISABLE_VBR) && !defined(DISABLE_FLOAT_API)
   case SPEEX_SET_VBR_QUALITY:
      st->vbr_quality = (*(float*)ptr);
      break;
   case SPEEX_GET_VBR_QUALITY:
      (*(float*)ptr) = st->vbr_quality;
      break;
#endif /* !defined(DISABLE_VBR) && !defined(DISABLE_FLOAT_API) */
   case SPEEX_SET_QUALITY:
      {
         int quality = (*(spx_int32_t*)ptr);
         if (quality < 0)
            quality = 0;
         if (quality > 10)
            quality = 10;
         st->submodeSelect = st->submodeID = ((const SpeexNBMode*)(st->mode->mode))->quality_map[quality];
      }
      break;
   case SPEEX_SET_COMPLEXITY:
      st->complexity = (*(spx_int32_t*)ptr);
      if (st->complexity<0)
         st->complexity=0;
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
      if (st->submodes[st->submodeID])
         (*(spx_int32_t*)ptr) = st->sampling_rate*SUBMODE(bits_per_frame)/st->frameSize;
      else
         (*(spx_int32_t*)ptr) = st->sampling_rate*(NB_SUBMODE_BITS+1)/st->frameSize;
      break;
   case SPEEX_SET_SAMPLING_RATE:
      st->sampling_rate = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_GET_SAMPLING_RATE:
      (*(spx_int32_t*)ptr)=st->sampling_rate;
      break;
   case SPEEX_RESET_STATE:
      {
         int i;
         st->bounded_pitch = 1;
         st->first = 1;
         for (i=0;i<st->lpcSize;i++)
            st->old_lsp[i]= DIV32(MULT16_16(QCONST16(3.1415927f, LSP_SHIFT), i+1), st->lpcSize+1);
         for (i=0;i<st->lpcSize;i++)
            st->mem_sw[i]=st->mem_sw_whole[i]=st->mem_sp[i]=st->mem_exc[i]=0;
         for (i=0;i<st->frameSize+st->max_pitch+1;i++)
            st->excBuf[i]=st->swBuf[i]=0;
         for (i=0;i<st->windowSize-st->frameSize;i++)
            st->winBuf[i]=0;
      }
      break;
   case SPEEX_SET_SUBMODE_ENCODING:
      st->encode_submode = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_GET_SUBMODE_ENCODING:
      (*(spx_int32_t*)ptr) = st->encode_submode;
      break;
   case SPEEX_GET_LOOKAHEAD:
      (*(spx_int32_t*)ptr)=(st->windowSize-st->frameSize);
      break;
   case SPEEX_SET_PLC_TUNING:
      st->plc_tuning = (*(spx_int32_t*)ptr);
      if (st->plc_tuning>100)
         st->plc_tuning=100;
      break;
   case SPEEX_GET_PLC_TUNING:
      (*(spx_int32_t*)ptr)=(st->plc_tuning);
      break;
#ifndef DISABLE_VBR
   case SPEEX_SET_VBR_MAX_BITRATE:
      st->vbr_max = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_GET_VBR_MAX_BITRATE:
      (*(spx_int32_t*)ptr) = st->vbr_max;
      break;
#endif /* #ifndef DISABLE_VBR */
   case SPEEX_SET_HIGHPASS:
      st->highpass_enabled = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_GET_HIGHPASS:
      (*(spx_int32_t*)ptr) = st->highpass_enabled;
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
            ((spx_word16_t*)ptr)[i] = compute_rms16(st->exc+i*st->subframeSize, st->subframeSize);
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
      st->isWideband = *((spx_int32_t*)ptr);
      break;
   case SPEEX_GET_STACK:
      *((char**)ptr) = st->stack;
      break;
   default:
      speex_warning_int("Unknown nb_ctl request: ", request);
      return -1;
   }
