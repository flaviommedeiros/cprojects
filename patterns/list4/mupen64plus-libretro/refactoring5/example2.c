#ifdef RAM_OFFSET
if(c) emit_movsbl_indexed(x,tl,tl);
          else
#endif
          emit_movsbl_indexed_tlb(x,tl,map,tl);
