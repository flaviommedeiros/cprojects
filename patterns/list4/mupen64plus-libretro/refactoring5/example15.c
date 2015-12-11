#ifdef HOST_IMM_ADDR32
if(c) emit_readdword_tlb(constmap[i][s]+offset,map,th,tl);
    else
    #endif
#ifdef RAM_OFFSET
       if (c)
       {
          emit_readword_indexed(0, tl, th);
          emit_readword_indexed(4, tl, tl);
       }
