if (d->force_loops) {
    loop = d->force_loops;
    TRACE68(sc68_cat,"libsc68: disk has a forced loop -- %02d\n",loop);
  }
#ifdef WITH_FORCE
  else if (loop == SC68_DEF_LOOP && sc68->cfg_loop != SC68_DEF_LOOP) {
    loop = sc68->cfg_loop;
    TRACE68(sc68_cat,"libsc68: config has a forced loop -- %02d\n", loop);
  }
#endif
