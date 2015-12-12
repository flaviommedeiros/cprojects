switch (file_type_get(file))
    {
      case FILE_REGULAR:
	filescanner_process_media(file, mtime, size, type, NULL);

	cache_artwork_ping(file, mtime, !is_bulkscan);
	// TODO [artworkcache] If entry in artwork cache exists for no artwork available, delete the entry if media file has embedded artwork

	counter++;

	/* When in bulk mode, split transaction in pieces of 200 */
	if ((flags & F_SCAN_BULK) && (counter % 200 == 0))
	  {
	    DPRINTF(E_LOG, L_SCAN, "Scanned %d files...\n", counter);
	    db_transaction_end();
	    db_transaction_begin();
	  }
	break;

      case FILE_PLAYLIST:
      case FILE_ITUNES:
	if (flags & F_SCAN_BULK)
	  defer_playlist(file, mtime);
	else
	  process_playlist(file, mtime);
	break;

      case FILE_SMARTPL:
	DPRINTF(E_DBG, L_SCAN, "Smart playlist file: %s\n", file);
	scan_smartpl(file, mtime);
	break;

      case FILE_ARTWORK:
	DPRINTF(E_DBG, L_SCAN, "Artwork file: %s\n", file);
	cache_artwork_ping(file, mtime, !is_bulkscan);

	// TODO [artworkcache] If entry in artwork cache exists for no artwork available for a album with files in the same directory, delete the entry

	break;

      case FILE_CTRL_REMOTE:
	remote_pairing_read_pin(file);
	break;

#ifdef LASTFM
      case FILE_CTRL_LASTFM:
	lastfm_login(file);
	break;
#endif

#ifdef HAVE_SPOTIFY_H
      case FILE_CTRL_SPOTIFY:
	spotify_login(file);
	break;
#endif

      case FILE_CTRL_INITSCAN:
	if (flags & F_SCAN_BULK)
	  break;

	DPRINTF(E_LOG, L_SCAN, "Startup rescan triggered, found init-rescan file: %s\n", file);

	filescanner_initscan(NULL);
	break;

      case FILE_CTRL_FULLSCAN:
	if (flags & F_SCAN_BULK)
	  break;

	DPRINTF(E_LOG, L_SCAN, "Full rescan triggered, found full-rescan file: %s\n", file);

	filescanner_fullrescan(NULL);
	break;

      default:
	DPRINTF(E_WARN, L_SCAN, "Ignoring file: %s\n", file);
    }
