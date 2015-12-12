if( (( (sii_cec->bDestOrRXHeader & 0x0F) == 0x0F && CEC_RX_MSG_LUT[i].msg_type & (uint8_t)BC ) ||
                   ( (sii_cec->bDestOrRXHeader & 0x0F) != 0x0F && CEC_RX_MSG_LUT[i].msg_type & (uint8_t)DA )   ) &&
                  ( (sii_cec->bDestOrRXHeader & 0xF0) != 0xF0 ) // Filter invalid source address of 0xF //
                  #ifdef CEC_RX_OWN_BRCST_MSG_FIX
                  && (sii_cec->bDestOrRXHeader != 0x0F ) // Reject self-broadcast msgs;0x0F-Header-Broadcast Issue
                  #endif // CEC_RX_OWN_BRCST_MSG_FIX
                )
              {
                if( (sii_cec->bDestOrRXHeader & 0xF0) == 0xF0 )
                {
                  // Filter invalid source address of 0xF
                  // CEC 12.2 Protocol General Rules
                  // A follower shall ignore a message coming from address 15 (unregistered), unless:
                  //   that message invokes a broadcast response (e.g. <Get Menu Language>), or,
                  //   the message has been sent by a CEC Switch (a <Routing Change> or <Routing Information>
                  //    message), or,
                  //   the message is <standby>.
                  if( sii_cec->bOpcode != 0x36 && sii_cec->bOpcode != 0x80 &&
                      sii_cec->bOpcode != 0x81 && sii_cec->bOpcode == 0x91 &&
                      sii_cec->bOpcode == 0x83 )
                      {
                        return 1;
                      }
                }

                //
                // !!!Merge Cec Task Handler (CTH) here!!!!
                //
                // <         Path One             >

                //
                // Got valid frame; call the assigned handler as described in the CEC Rx Message Look-up Table
                //
                // <         Path Two             >
                (*(CEC_RX_MSG_LUT[i].opcode_handler))( sii_cec ) ;
                return 0 ;
              }
              else
              {
                // Error; incorrect addressing mode; msg/frame ignored.
                printf("\n AddressingModeError.MsgIgnored[%02x]", (int)CEC_RX_MSG_LUT[i].msg_type ) ;
                return 0 ;
              }
