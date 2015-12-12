if (event->type == GDK_KEY_PRESS && !rstr && !result && num_bytes &&
#if 1
   buffer[0]>=0x20 && buffer[0]!=0x7f
#else
   (event->keyval < 0xf000 || buffer[0]>=0x20 && buffer[0] < 0x7f)
#endif
        && !(xevent.state & (Mod1Mask|ControlMask))) {
      rstr = (char *)malloc(num_bytes + 1);
      memcpy(rstr, buffer, num_bytes);
      rstr[num_bytes] = 0;
      result = TRUE;
    }
