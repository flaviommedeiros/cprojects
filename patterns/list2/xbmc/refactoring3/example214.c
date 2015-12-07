switch (address)
   {
   case APU_SMASK:
      /* seems that bit 6 denotes vblank -- return 1 for now */
      value = 0x40;

      /* Return 1 in 0-5 bit pos if a channel is playing */
      if (apu->rectangle[0].enabled && apu->rectangle[0].vbl_length)
         value |= 0x01;
      if (apu->rectangle[1].enabled && apu->rectangle[1].vbl_length)
         value |= 0x02;
      if (apu->triangle.enabled && apu->triangle.vbl_length)
         value |= 0x04;
      if (apu->noise.enabled && apu->noise.vbl_length)
         value |= 0x08;

      //if (apu->dmc.dma_length)
      /* bodge for timestamp queue */
      if (apu->dmc.enabled)
         value |= 0x10;

      if (apu->dmc.irq_occurred)
         value |= 0x80;

      break;

#ifndef NSF_PLAYER
   case APU_JOY0:
      value = input_get(INP_JOYPAD0);
      break;

   case APU_JOY1:
      value = input_get(INP_ZAPPER | INP_JOYPAD1 /*| INP_ARKANOID*/ /*| INP_POWERPAD*/);
      break;
#endif /* !NSF_PLAYER */

   default:
      value = (address >> 8); /* heavy capacitance on data bus */
      break;
   }
