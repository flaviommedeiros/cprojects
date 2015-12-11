static void ares_query_completed_cb(void *arg,  /* (struct connectdata *) */
                                    int status,
#ifdef HAVE_CARES_CALLBACK_TIMEOUTS
                                    int timeouts,
#endif
                                    struct hostent *hostent)
{
  struct connectdata *conn = (struct connectdata *)arg;
  struct Curl_addrinfo * ai = NULL;

#ifdef HAVE_CARES_CALLBACK_TIMEOUTS
  (void)timeouts; /* ignored */
#endif

  if (status == CURL_ASYNC_SUCCESS) {
    ai = Curl_he2ai(hostent, conn->async.port);
  }

  (void)Curl_addrinfo_callback(arg, status, ai);
}
