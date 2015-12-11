#ifdef HOST_IMM_ADDR32
if(c)
          emit_readdword_tlb(constmap[i][s]+offset,map,th,tl);
        else
        #endif
#ifdef RAM_OFFSET
           if (c)
           {
              if (th >= 0) emit_readword_indexed(0, addr, th);
              emit_readword_indexed(4, addr, tl);
           }
