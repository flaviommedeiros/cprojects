if( (sii_cec->bDestOrRXHeader & 0x0F) != 0x0F
      #ifdef CEC_RX_OWN_BRCST_MSG_FIX
      && (sii_cec->bDestOrRXHeader != 0x0F ) // Workaround for 0x0F-Header-Broadcast Issue
      #endif // CEC_RX_OWN_BRCST_MSG_FIX
      )
    {
      //
      // Unsupported opcode; send f e a t u r e   a b o r t
      //
      cec_frame.bOpcode = 0x00;
      cec_frame.bDestOrRXHeader = (sii_cec->bDestOrRXHeader & 0xf0) >> 4 ;
      cec_frame.bOperand[0] = sii_cec->bOpcode;
      cec_frame.bOperand[1] = 0;
      cec_frame.bCount = 2;
      SiI_CEC_SetCommand( &cec_frame );
      printf("\n!UnsupportedFeature!");
    }
    else
    {
      //
      // Unsupported Broadcast Msg
      //
      printf("\n!UnsupportedBcMsg!");
    }
