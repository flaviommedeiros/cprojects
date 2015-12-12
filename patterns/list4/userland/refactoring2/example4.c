#if (MAX_MISORDER != 0)
if (udelta <= RTP_SEQ_MOD - MAX_MISORDER)
#endif
      {
         /* the sequence number made a very large jump */
         if (seq == t_module->bad_seq)
         {
            LOG_INFO(0, "RTP: Misorder restart at 0x%4.4hx", seq);
            /* Two sequential packets -- assume that the other side
             * restarted without telling us so just re-sync
             * (i.e., pretend this was the first packet). */
            init_sequence_number(t_module, seq);
         } else {
            LOG_INFO(0, "RTP: Misorder at 0x%4.4hx, expected 0x%4.4hx", seq, t_module->max_seq_num);
            t_module->bad_seq = (seq + 1) & (RTP_SEQ_MOD-1);
            return 0;
         }
      }
#if (MAX_MISORDER != 0)
   else {
      /* duplicate or reordered packet */

      /* TODO: handle out of order packets */
   }
