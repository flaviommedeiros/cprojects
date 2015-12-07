if (INB (OBOE_ENABLEH) & OBOE_ENABLEH_FIRON)
            {
              ctl |= OBOE_CTL_TX_BAD_CRC | OBOE_CTL_TX_SIP ;
            }
#ifdef USE_MIR
          else if (INB (OBOE_ENABLEH) & OBOE_ENABLEH_MIRON)
            {
              ctl |= OBOE_CTL_TX_BAD_CRC;
            }
#endif
