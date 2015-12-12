#ifdef VIO_USE_DONTWAIT
if (vio->type == VIO_TYPE_SSL)
#endif
  {
    /* Deduce what should be the new blocking mode of the socket. */
    my_bool new_mode= vio->write_timeout < 0 && vio->read_timeout < 0;

    /* If necessary, update the blocking mode. */
    if (new_mode != old_mode)
      ret= vio_set_blocking(vio, new_mode);
  }
