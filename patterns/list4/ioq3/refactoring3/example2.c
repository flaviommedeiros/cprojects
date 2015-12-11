switch(request)
   {
   case SPEEX_PREPROCESS_SET_DENOISE:
      st->denoise_enabled = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_PREPROCESS_GET_DENOISE:
      (*(spx_int32_t*)ptr) = st->denoise_enabled;
      break;
#ifndef FIXED_POINT
   case SPEEX_PREPROCESS_SET_AGC:
      st->agc_enabled = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_PREPROCESS_GET_AGC:
      (*(spx_int32_t*)ptr) = st->agc_enabled;
      break;
#ifndef DISABLE_FLOAT_API
   case SPEEX_PREPROCESS_SET_AGC_LEVEL:
      st->agc_level = (*(float*)ptr);
      if (st->agc_level<1)
         st->agc_level=1;
      if (st->agc_level>32768)
         st->agc_level=32768;
      break;
   case SPEEX_PREPROCESS_GET_AGC_LEVEL:
      (*(float*)ptr) = st->agc_level;
      break;
#endif /* #ifndef DISABLE_FLOAT_API */
   case SPEEX_PREPROCESS_SET_AGC_INCREMENT:
      st->max_increase_step = exp(0.11513f * (*(spx_int32_t*)ptr)*st->frame_size / st->sampling_rate);
      break;
   case SPEEX_PREPROCESS_GET_AGC_INCREMENT:
      (*(spx_int32_t*)ptr) = floor(.5+8.6858*log(st->max_increase_step)*st->sampling_rate/st->frame_size);
      break;
   case SPEEX_PREPROCESS_SET_AGC_DECREMENT:
      st->max_decrease_step = exp(0.11513f * (*(spx_int32_t*)ptr)*st->frame_size / st->sampling_rate);
      break;
   case SPEEX_PREPROCESS_GET_AGC_DECREMENT:
      (*(spx_int32_t*)ptr) = floor(.5+8.6858*log(st->max_decrease_step)*st->sampling_rate/st->frame_size);
      break;
   case SPEEX_PREPROCESS_SET_AGC_MAX_GAIN:
      st->max_gain = exp(0.11513f * (*(spx_int32_t*)ptr));
      break;
   case SPEEX_PREPROCESS_GET_AGC_MAX_GAIN:
      (*(spx_int32_t*)ptr) = floor(.5+8.6858*log(st->max_gain));
      break;
#endif
   case SPEEX_PREPROCESS_SET_VAD:
      speex_warning("The VAD has been replaced by a hack pending a complete rewrite");
      st->vad_enabled = (*(spx_int32_t*)ptr);
      break;
   case SPEEX_PREPROCESS_GET_VAD:
      (*(spx_int32_t*)ptr) = st->vad_enabled;
      break;
   
   case SPEEX_PREPROCESS_SET_DEREVERB:
      st->dereverb_enabled = (*(spx_int32_t*)ptr);
      for (i=0;i<st->ps_size;i++)
         st->reverb_estimate[i]=0;
      break;
   case SPEEX_PREPROCESS_GET_DEREVERB:
      (*(spx_int32_t*)ptr) = st->dereverb_enabled;
      break;

   case SPEEX_PREPROCESS_SET_DEREVERB_LEVEL:
      /* FIXME: Re-enable when de-reverberation is actually enabled again */
      /*st->reverb_level = (*(float*)ptr);*/
      break;
   case SPEEX_PREPROCESS_GET_DEREVERB_LEVEL:
      /* FIXME: Re-enable when de-reverberation is actually enabled again */
      /*(*(float*)ptr) = st->reverb_level;*/
      break;
   
   case SPEEX_PREPROCESS_SET_DEREVERB_DECAY:
      /* FIXME: Re-enable when de-reverberation is actually enabled again */
      /*st->reverb_decay = (*(float*)ptr);*/
      break;
   case SPEEX_PREPROCESS_GET_DEREVERB_DECAY:
      /* FIXME: Re-enable when de-reverberation is actually enabled again */
      /*(*(float*)ptr) = st->reverb_decay;*/
      break;

   case SPEEX_PREPROCESS_SET_PROB_START:
      *(spx_int32_t*)ptr = MIN32(100,MAX32(0, *(spx_int32_t*)ptr));
      st->speech_prob_start = DIV32_16(MULT16_16(Q15ONE,*(spx_int32_t*)ptr), 100);
      break;
   case SPEEX_PREPROCESS_GET_PROB_START:
      (*(spx_int32_t*)ptr) = MULT16_16_Q15(st->speech_prob_start, 100);
      break;

   case SPEEX_PREPROCESS_SET_PROB_CONTINUE:
      *(spx_int32_t*)ptr = MIN32(100,MAX32(0, *(spx_int32_t*)ptr));
      st->speech_prob_continue = DIV32_16(MULT16_16(Q15ONE,*(spx_int32_t*)ptr), 100);
      break;
   case SPEEX_PREPROCESS_GET_PROB_CONTINUE:
      (*(spx_int32_t*)ptr) = MULT16_16_Q15(st->speech_prob_continue, 100);
      break;

   case SPEEX_PREPROCESS_SET_NOISE_SUPPRESS:
      st->noise_suppress = -ABS(*(spx_int32_t*)ptr);
      break;
   case SPEEX_PREPROCESS_GET_NOISE_SUPPRESS:
      (*(spx_int32_t*)ptr) = st->noise_suppress;
      break;
   case SPEEX_PREPROCESS_SET_ECHO_SUPPRESS:
      st->echo_suppress = -ABS(*(spx_int32_t*)ptr);
      break;
   case SPEEX_PREPROCESS_GET_ECHO_SUPPRESS:
      (*(spx_int32_t*)ptr) = st->echo_suppress;
      break;
   case SPEEX_PREPROCESS_SET_ECHO_SUPPRESS_ACTIVE:
      st->echo_suppress_active = -ABS(*(spx_int32_t*)ptr);
      break;
   case SPEEX_PREPROCESS_GET_ECHO_SUPPRESS_ACTIVE:
      (*(spx_int32_t*)ptr) = st->echo_suppress_active;
      break;
   case SPEEX_PREPROCESS_SET_ECHO_STATE:
      st->echo_state = (SpeexEchoState*)ptr;
      break;
   case SPEEX_PREPROCESS_GET_ECHO_STATE:
      ptr = (void*)st->echo_state;
      break;
#ifndef FIXED_POINT
   case SPEEX_PREPROCESS_GET_AGC_LOUDNESS:
      (*(spx_int32_t*)ptr) = pow(st->loudness, 1.0/LOUDNESS_EXP);
      break;
#endif

   default:
      speex_warning_int("Unknown speex_preprocess_ctl request: ", request);
      return -1;
   }
