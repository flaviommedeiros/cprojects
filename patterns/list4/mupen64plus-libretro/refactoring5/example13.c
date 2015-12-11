#ifdef HOST_IMM_ADDR32
if(c) emit_readword_tlb(constmap[i][s]+offset,map,tl);
    else
    #endif
#ifdef RAM_OFFSET
       if(c) emit_readword_indexed(0,tl,tl);
