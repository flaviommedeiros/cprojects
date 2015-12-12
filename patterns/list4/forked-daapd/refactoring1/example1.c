if (ft == FILE_PLAYLIST)
    scan_playlist(file, mtime);
#ifdef ITUNES
  else if (ft == FILE_ITUNES)
    scan_itunes_itml(file);
#endif
