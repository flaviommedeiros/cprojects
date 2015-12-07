#ifdef ENABLE_X509_TRACK
if (x509_track)
    x509_setenv_track (x509_track, es, cert_depth, peer_cert);
  else
#endif
    x509_setenv (es, cert_depth, peer_cert);
