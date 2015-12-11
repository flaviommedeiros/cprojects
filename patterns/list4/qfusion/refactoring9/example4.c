static void query_completed_cb(void *arg,  /* (struct connectdata *) */
                               int status,
#ifdef HAVE_CARES_CALLBACK_TIMEOUTS
                               int timeouts,
#endif
                               struct hostent *hostent)
{
  struct connectdata *conn = (struct connectdata *)arg;
  struct ResolverResults *res;

#ifdef HAVE_CARES_CALLBACK_TIMEOUTS
  (void)timeouts; /* ignored */
#endif

  if(ARES_EDESTRUCTION == status)
    /* when this ares handle is getting destroyed, the 'arg' pointer may not
       be valid so only defer it when we know the 'status' says its fine! */
    return;

  res = (struct ResolverResults *)conn->async.os_specific;
  res->num_pending--;

  if(CURL_ASYNC_SUCCESS == status) {
    Curl_addrinfo *ai = Curl_he2ai(hostent, conn->async.port);
    if(ai) {
      compound_results(res, ai);
    }
  }
  /* A successful result overwrites any previous error */
  if(res->last_status != ARES_SUCCESS)
    res->last_status = status;
}
