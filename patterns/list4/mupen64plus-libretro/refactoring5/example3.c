#ifdef HOST_IMM_ADDR32
if(c)
          emit_movswl_tlb((constmap[i][s]+offset)^2,map,tl);
        else
        #endif
        {
          int x=0;
          if(!c) emit_xorimm(addr,2,tl);
          else x=((constmap[i][s]+offset)^2)-(constmap[i][s]+offset);
          //#ifdef
          //emit_movswl_indexed_tlb(x,tl,map,tl);
          //else
          if(map>=0) {
            gen_tlb_addr_r(tl,map);
            emit_movswl_indexed(x,tl,tl);
          }else{
            #ifdef RAM_OFFSET
             if(!c) gen_tlb_addr_r(tl,-1);
            emit_movswl_indexed(x,tl,tl);
            #else
            emit_movswl_indexed((intptr_t)g_rdram-0x80000000+x,tl,tl);
            #endif
          }
        }