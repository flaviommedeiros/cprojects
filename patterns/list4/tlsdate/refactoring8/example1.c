void
trigger_event (struct state *state, enum event_id_t id, int sec)
{
#ifdef WITH_EVENTS
  struct event *e = state->events[id];
  struct timeval delay = { sec, 0 };
  /* Fallthrough to tlsdate if there is no resolver. */
  if (!e && id == E_RESOLVER)
    e = state->events[E_TLSDATE];
  if (!e)
    {
      info ("trigger_event with NULL |e|. I hope this is a test!");
      return;
    }
  if (event_pending (e, EV_READ|EV_WRITE|EV_TIMEOUT|EV_SIGNAL, NULL))
    event_del (e);
  if (sec >= 0)
    event_add (e, &delay);
  else /* Note! This will not fire a TIMEOUT event. */
    event_add (e, NULL);
#endif
}
