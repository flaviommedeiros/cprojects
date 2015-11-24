#ifdef PPPOE_TODO
if (sc->sc_service_name != NULL) {
    PPPOE_ADD_16(p, l1);
    MEMCPY(p, sc->sc_service_name, l1);
    p += l1;
  } else
#endif /* PPPOE_TODO */
  {
    PPPOE_ADD_16(p, 0);
  }
