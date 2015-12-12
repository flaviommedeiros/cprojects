#ifdef HOST_IMM_ADDR32
if(c)
          emit_movsbl(constaddr^1,t);
        else
        #endif
        {
          int x=0;
          emit_movsbl_indexed_map(x,t,map,t);
        }
