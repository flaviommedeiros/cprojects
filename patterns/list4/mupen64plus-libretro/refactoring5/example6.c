#ifdef RAM_OFFSET
if(c) emit_movzbl_indexed(x,tl,tl);
          else
#endif
          emit_movzbl_indexed_tlb(x,tl,map,tl);
