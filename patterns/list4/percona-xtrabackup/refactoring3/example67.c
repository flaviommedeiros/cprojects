switch (count) {
    /* Fall through all cases!!! */
#ifdef UNICODE_32BIT
    case 6: r[5] = (uchar) (0x80 | (wc & 0x3f)); wc = wc >> 6; wc |= 0x4000000;
    case 5: r[4] = (uchar) (0x80 | (wc & 0x3f)); wc = wc >> 6; wc |= 0x200000;
    case 4: r[3] = (uchar) (0x80 | (wc & 0x3f)); wc = wc >> 6; wc |= 0x10000;
#endif
    case 3: r[2] = (uchar) (0x80 | (wc & 0x3f)); wc = wc >> 6; wc |= 0x800;
    case 2: r[1] = (uchar) (0x80 | (wc & 0x3f)); wc = wc >> 6; wc |= 0xc0;
    case 1: r[0] = (uchar) wc;
  }
