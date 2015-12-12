if ((mode < 2 || leftright)
#ifdef Honor_FLT_ROUNDS
      && rounding == 1
#endif
     )
  {
    if (!word1(&u) && !(word0(&u) & Bndry_mask) &&
        word0(&u) & (Exp_mask & ~Exp_msk1)
       )
    {
      /* The special case */
      b2+= Log2P;
      s2+= Log2P;
      spec_case= 1;
    }
  }
