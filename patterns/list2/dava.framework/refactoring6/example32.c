if(_enc->mb_info==NULL||_enc->frag_dc==NULL||_enc->coded_mbis==NULL||
   _enc->mcu_skip_ssd==NULL||_enc->dct_tokens[0]==NULL||
   _enc->dct_tokens[1]==NULL||_enc->dct_tokens[2]==NULL||
   _enc->extra_bits[0]==NULL||_enc->extra_bits[1]==NULL||
   _enc->extra_bits[2]==NULL
#if defined(OC_COLLECT_METRICS)
   ||_enc->frag_satd==NULL||_enc->frag_ssd==NULL
#endif
   ){
    oc_enc_clear(_enc);
    return TH_EFAULT;
  }
