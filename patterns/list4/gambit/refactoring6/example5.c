if (!SetCommTimeouts (h, &cto)
#ifdef USE_BIG_SERIAL_BUFFERS
      || !SetupComm (h, 65536, 65536))
