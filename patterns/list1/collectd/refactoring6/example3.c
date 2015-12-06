if ((state > TCP_STATE_MAX)
#if TCP_STATE_MIN > 0
      || (state < TCP_STATE_MIN)
#endif
     )
  {
    NOTICE ("tcpconns plugin: Ignoring connection with "
	"unknown state 0x%02"PRIx8".", state);
    return (-1);
  }
