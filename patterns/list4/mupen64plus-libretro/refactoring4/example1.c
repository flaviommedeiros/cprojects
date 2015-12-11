#ifdef EMU_PCSXR
if(opcode[i]==0x2a||opcode[i]==0x2e||opcode[i]==0x2c||opcode[i]==0x2d)
#else
  // Also 64-bit SDL/SDR
  if(opcode[i]==0x2c||opcode[i]==0x2d)
#endif
    hsn[FTEMP]=0;
