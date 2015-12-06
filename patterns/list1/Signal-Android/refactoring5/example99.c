#ifndef DISABLE_VBR
if (st->dtx_count)
         speex_bits_pack(bits, 15, 4);
      else
#endif
         speex_bits_pack(bits, 0, 4);
