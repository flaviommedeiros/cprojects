#ifdef HOST_IMM_ADDR32
if(c)
          emit_movzbl_tlb((constmap[i][s]+offset)^3,map,tl);
        else
        #endif
        {
          //emit_xorimm(addr,3,tl);
          //gen_tlb_addr_r(tl,map);
          //emit_movzbl_indexed((int)g_rdram-0x80000000,tl,tl);
          int x=0;
          if(!c) emit_xorimm(addr,3,tl);
          else x=((constmap[i][s]+offset)^3)-(constmap[i][s]+offset);
          emit_movzbl_indexed_tlb(x,tl,map,tl);
        }
