#if defined(__APPLE__)
if (uv__fsevents_close(handle))
#endif /* defined(__APPLE__) */
  {
    uv__io_close(handle->loop, &handle->event_watcher);
  }
