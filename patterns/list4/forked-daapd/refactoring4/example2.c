#ifdef HAVE_EUIDACCESS
if (euidaccess(path, R_OK) < 0)
#else
      if (access(path, R_OK) < 0)
#endif
	{
	  DPRINTF(E_LOG, L_SCAN, "File access to '%s' failed: %s\n", path, strerror(errno));

	  db_file_delete_bypath(path);
	  cache_artwork_delete_by_path(path);
	}
      else if ((file_type_get(path) == FILE_REGULAR) && (db_file_id_bypath(path) <= 0)) // TODO Playlists
	{
	  DPRINTF(E_LOG, L_SCAN, "File access to '%s' achieved\n", path);

	  ie->mask |= IN_CLOSE_WRITE;
	}
