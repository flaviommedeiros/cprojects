#ifdef USE_MINI_HT
if(rs1[i]==PR) {
        do_miniht_jump(rs,rh,ht);
      }
      else
      #endif
      {
        emit_jmp(jump_vaddr_reg[slave][rs]);
      }
