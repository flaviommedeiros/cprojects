#ifdef HAVE_LIBZ
if(!ServerConfCompressed(server_p))
#endif
        ClearCap(client_p, CAP_ZIP);
