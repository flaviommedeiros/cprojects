if ((len != ((iLBC_Enc_Inst_t*)iLBCenc_inst)->blockl) &&
#ifdef SPLIT_10MS
      (len != 80) &&
#endif
      (len != 2*((iLBC_Enc_Inst_t*)iLBCenc_inst)->blockl) &&
      (len != 3*((iLBC_Enc_Inst_t*)iLBCenc_inst)->blockl))
  {
    /* A maximum of 3 frames/packet is allowed */
    return(-1);
  } else {

    /* call encoder */
    while (pos<len) {
      WebRtcIlbcfix_EncodeImpl((uint16_t*) &encoded[encpos], &speechIn[pos], (iLBC_Enc_Inst_t*) iLBCenc_inst);
#ifdef SPLIT_10MS
      pos += 80;
      if(((iLBC_Enc_Inst_t*)iLBCenc_inst)->section == 0)
#else
        pos += ((iLBC_Enc_Inst_t*)iLBCenc_inst)->blockl;
#endif
      encpos += ((iLBC_Enc_Inst_t*)iLBCenc_inst)->no_of_words;
    }
    return (encpos*2);
  }
