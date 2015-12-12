#ifdef HOST_IMM_ADDR32
if(c)
          emit_movzwl_tlb((constmap[i][s]+offset)^2,map,tl);
        else
        #endif
        {
          int x=0;
          if(!c) emit_xorimm(addr,2,tl);
          else x=((constmap[i][s]+offset)^2)-(constmap[i][s]+offset);
          //#ifdef
          //emit_movzwl_indexed_tlb(x,tl,map,tl);
          //#else
          if(map>=0) {
            gen_tlb_addr_r(tl,map);
            emit_movzwl_indexed(x,tl,tl);
          }else{
            #ifdef RAM_OFFSET
            emit_movzwl_indexed(x,tl,tl);
            #else
            emit_movzwl_indexed((int)g_rdram-0x80000000+x,tl,tl);
            #endif
          }
        }
