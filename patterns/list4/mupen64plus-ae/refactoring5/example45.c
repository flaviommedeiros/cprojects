#ifdef HOST_IMM_ADDR32
if(c)
          emit_readdword_tlb(constmap[i][s]+offset,map,th,tl);
        else
        #endif
        emit_readdword_indexed_tlb(0,addr,map,th,tl);
