#ifdef HOST_IMM_ADDR32
if(c)
          emit_movswl(constaddr,t);
        else
        #endif
        {
          int x=0;
          emit_movswl_indexed_map(0,addr,map,t);
        }
