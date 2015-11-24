#ifdef SPLIT_10MS
if(((iLBC_Enc_Inst_t*)iLBCenc_inst)->section == 0)
#else
        pos += ((iLBC_Enc_Inst_t*)iLBCenc_inst)->blockl;
