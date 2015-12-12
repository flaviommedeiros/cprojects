if (
#ifdef HAVE_STRUCT_DIRENT_D_TYPE
		/* don't use g_file_test at first so we don't stat() */
		    dent->d_type == DT_DIR ||
		    (dent->d_type == DT_LNK &&
		     g_file_test (file, G_FILE_TEST_IS_DIR))
#else
		    g_file_test (file, G_FILE_TEST_IS_DIR)
#endif
		   )
			suffix = "/";
