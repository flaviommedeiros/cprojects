if ((D.dqb_curblocks>D.dqb_bsoftlimit)
#if !defined(__FreeBSD__) && !defined(__OpenBSD__) && !defined(__DragonFly__)
||((D.dqb_curfiles>D.dqb_fsoftlimit) && (D.dqb_fsoftlimit != 0))
#endif
    ) {
      *dfree = 0;
      *dsize = D.dqb_curblocks;
    }
  else {
    *dfree = D.dqb_bsoftlimit - D.dqb_curblocks;
    *dsize = D.dqb_bsoftlimit;
  }
