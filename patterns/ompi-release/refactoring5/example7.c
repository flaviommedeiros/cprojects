#ifdef VT_ETIMESYNC
if (vt_env_etimesync())
      vt_esync(MPI_COMM_WORLD);
    else
#endif /* VT_ETIMESYNC */
      vt_sync(MPI_COMM_WORLD, &my_ltime[0], &my_offset[0]);
