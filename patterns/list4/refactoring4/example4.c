#ifdef HOST_IMM_ADDR32
if((itype[i+1]!=LOAD&&opcode[i+1]!=0x31&&opcode[i+1]!=0x35) ||
             (using_tlb&&((signed int)constmap[i+1][rs]+offset)>=(signed int)0xC0000000))
          #endif
          #ifdef RAM_OFFSET
          if((itype[i+1]==LOAD||opcode[i+1]==0x31||opcode[i+1]==0x35)&&(signed int)constmap[i+1][rs]+offset<(signed int)0x80800000) 
          {
#if NEW_DYNAREC != NEW_DYNAREC_ARM
             emit_gen_ram_ptr(constmap[i+1][rs]+offset,ra);
#else
             emit_movimm(constmap[i+1][rs]+offset+(intptr_t)g_rdram-0x80000000,ra);
#endif
          }
          else
          #endif
          emit_movimm(constmap[i+1][rs]+offset,ra);
