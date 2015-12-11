#ifdef HOST_IMM_ADDR32
if(c)
          emit_readword_tlb(constmap[i][s]+offset,map,tl);
        else
        #endif
        #ifdef RAM_OFFSET
        // This case is for x86-64 with 64-bit pointers
        // (not using HOST_IMM_ADDR32) and offset (map) is not in a register
        if(c) emit_readword_indexed(0,addr,tl);
        else
        #endif
        emit_readword_indexed_tlb(0,addr,map,tl);
