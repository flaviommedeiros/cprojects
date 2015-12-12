#ifdef HAVE_EUIDACCESS
if (euidaccess(path, (R_OK | X_OK)) < 0)
#else
      if (access(path, (R_OK | X_OK)) < 0)
#endif
	{
	  DPRINTF(E_LOG, L_SCAN, "Directory access to '%s' failed: %s\n", path, strerror(errno));

	  if (ret == 0)
	    watches_clear(wi->wd, path);

	  db_file_disable_bymatch(path, "", 0);
	  db_pl_disable_bymatch(path, "", 0);
	}
      else if (ret < 0)
	{
	  DPRINTF(E_LOG, L_SCAN, "Directory access to '%s' achieved\n", path);

	  ie->mask |= IN_CREATE;
	}
      else
	{
	  DPRINTF(E_INFO, L_SCAN, "Directory event, but '%s' already being watched\n", path);
	}
