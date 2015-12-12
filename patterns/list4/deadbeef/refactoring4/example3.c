#ifdef _WIN32
if (mkdir (on_disk_directory) != 0)
#else
	      if (mkdir (on_disk_directory, 0777) != 0)
#endif
		{
#ifndef _WIN32
/* This happens under WIN32 when stat is confused by the filename, but this is
   harmless, since we know that the directory exists after all. */
		  error = glade_error_new_system (_("Couldn't create directory:\n  %s\n"), directory);
#endif
		}
