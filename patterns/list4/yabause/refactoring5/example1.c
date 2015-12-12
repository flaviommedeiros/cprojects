#ifdef EXEC_FROM_CACHE
if ((addr & 0xC0000000) == 0xC0000000) sh->instruction = DataArrayReadWord(addr);
   else
#endif
   sh->instruction = fetchlist[(addr >> 20) & 0x0FF](addr);
