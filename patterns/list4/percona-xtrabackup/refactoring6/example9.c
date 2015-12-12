if (j1 == 0 && mode != 1 && !(word1(&u) & 1)
#ifdef Honor_FLT_ROUNDS
          && rounding >= 1
#endif
         )
      {
        if (dig == '9')
          goto round_9_up;
        if (j > 0)
          dig++;
        *s++= dig;
        goto ret;
      }
