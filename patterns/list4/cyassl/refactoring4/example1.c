#ifdef CYASSL_SMALL_STACK
if (ocspRespBuf != NULL && ocsp->cm->ocspRespFreeCb)
        ocsp->cm->ocspRespFreeCb(ocsp->cm->ocspIOCtx, ocspRespBuf);
