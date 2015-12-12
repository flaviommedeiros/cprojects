#ifdef HOST_IMM_ADDR32
if(c)
          emit_readword_tlb(constmap[i][s]+offset,map,tl);
        else
        #endif
        emit_readword_indexed_tlb(0,addr,map,tl);
