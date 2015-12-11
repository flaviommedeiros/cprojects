#ifdef USE_MINI_HT
if(rs1[i]==31) {
    do_miniht_jump(rs,rh,ht);
  }
  else
  #endif
  {
    //if(rs!=EAX) emit_mov(rs,EAX);
    //emit_jmp((int)jump_vaddr_eax);
    emit_jmp((intptr_t)jump_vaddr_reg[rs]);
  }
