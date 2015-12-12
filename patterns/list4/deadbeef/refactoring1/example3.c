if (!ptimer->tcr) {
    ptimer->tdr_cur = v;
    TRACE68(mfp_cat,
          MYHD "timer-%c -- reload TDR @%u -- %u\n",
            ptimer->def.letter, (unsigned) bogoc, (unsigned) ptimer->tdr_res);
  }
#ifndef NDEBUG
  else if (ptimer->tcr && v != old_tdr) {
    uint_t old_frq = timerfrq(old_tdr);
    TRACE68(mfp_cat,
            MYHD "timer-%c -- change @%u cti:%u psw:%u(%u) cpp:%u"
            " -- %u(%u) -> %u(%u)hz\n",
            ptimer->def.letter, (unsigned) bogoc, (unsigned) ptimer->cti,
            (unsigned) prediv_width[ptimer->tcr], (unsigned) ptimer->tcr,
            (unsigned) cpp(ptimer->tdr_res),
            (unsigned) old_frq, (unsigned) old_tdr,
            (unsigned) timerfrq(ptimer->tdr_res), (unsigned) ptimer->tdr_res);
  }
#endif
