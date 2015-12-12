#ifndef WIN32
if (access(".", R_OK | W_OK | X_OK) != 0)
#else
	if (win32_check_directory_write_permissions() != 0)
#endif
		pg_fatal("You must have read and write access in the current directory.\n");
