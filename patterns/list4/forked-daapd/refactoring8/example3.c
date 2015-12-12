static void
dacp_playstatus_update_handler(enum listener_event_type type)
{
  int ret;

  // Only send status update on player change events
  if (type != LISTENER_PLAYER)
    return;

#ifdef USE_EVENTFD
  ret = eventfd_write(update_efd, 1);
  if (ret < 0)
    DPRINTF(E_LOG, L_DACP, "Could not send status update event: %s\n", strerror(errno));
#else
  int dummy = 42;

  ret = write(update_pipe[1], &dummy, sizeof(dummy));
  if (ret != sizeof(dummy))
    DPRINTF(E_LOG, L_DACP, "Could not write to status update fd: %s\n", strerror(errno));
#endif
}
