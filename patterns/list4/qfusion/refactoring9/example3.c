static void mstate(struct SessionHandle *easy, CURLMstate state
#ifdef DEBUGBUILD
                   , int lineno
#endif
)
{
#ifdef DEBUGBUILD
  long connection_id = -5000;
#endif
  CURLMstate oldstate = easy->mstate;

  if(oldstate == state)
    /* don't bother when the new state is the same as the old state */
    return;

  easy->mstate = state;

#ifdef DEBUGBUILD
  if(easy->mstate >= CURLM_STATE_CONNECT_PEND &&
     easy->mstate < CURLM_STATE_COMPLETED) {
    if(easy->easy_conn)
      connection_id = easy->easy_conn->connection_id;

    infof(easy,
          "STATE: %s => %s handle %p; line %d (connection #%ld) \n",
          statename[oldstate], statename[easy->mstate],
          (void *)easy, lineno, connection_id);
  }
#endif
  if(state == CURLM_STATE_COMPLETED)
    /* changing to COMPLETED means there's one less easy handle 'alive' */
    easy->multi->num_alive--;
}
