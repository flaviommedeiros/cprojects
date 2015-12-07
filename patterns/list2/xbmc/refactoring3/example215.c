switch (address)
   {
   case 0x4015:
      /* bodge for timestamp queue */
      apu->dmc.enabled = (value & 0x10) ? TRUE : FALSE;

   case 0x4000: case 0x4001: case 0x4002: case 0x4003:
   case 0x4004: case 0x4005: case 0x4006: case 0x4007:
   case 0x4008: case 0x4009: case 0x400A: case 0x400B:
   case 0x400C: case 0x400D: case 0x400E: case 0x400F:
   case 0x4010: case 0x4011: case 0x4012: case 0x4013:
      d.timestamp = nes6502_getcycles(FALSE);
      d.address = address;
      d.value = value;
      apu_enqueue(&d);
      break;

#ifndef NSF_PLAYER
   case APU_OAMDMA:
      ppu_oamdma(address, value);
      break;

   case APU_JOY0:
      /* VS system VROM switching */
      mmc_vsvrom(value & 4);

      /* see if we need to strobe them joypads */
      value &= 1;
      if ((0 == value) && last_write)
         input_strobe();
      last_write = value;
      break;

   case APU_JOY1: /* Some kind of IRQ control business */
      break;

#endif /* !NSF_PLAYER */

   default:
      break;
   }
