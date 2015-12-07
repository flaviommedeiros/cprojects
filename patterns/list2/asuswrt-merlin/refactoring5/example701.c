#ifdef SUPPORT_UTF
if (utf)
              class_uchardata += PRIV(ord2utf)(0x10ffff, class_uchardata);
            else
#endif
              *class_uchardata++ = 0xffff;
