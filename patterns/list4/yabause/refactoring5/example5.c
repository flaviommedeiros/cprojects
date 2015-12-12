#ifdef HOST_IMM_ADDR32
if(c)
          emit_readword(constaddr,t);
        else
        #endif
        emit_readword_indexed_map(0,addr,map,t);
