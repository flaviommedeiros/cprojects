#if USE_THREADS
if (!rabin_th)
#endif
							{
								const char *filepath = NULL;
								if (debug) {
									// XXX: incorrect for PIE binaries
									filepath = file? strstr (file, "://"): NULL;
									filepath = filepath? filepath+3: pfile;
								}
								if (r.file && r.file->desc && r.file->desc->name)
									filepath = r.file->desc->name;

								/* Load rbin info from r2 dbg:// or r2 /bin/ls */
								/* the baddr should be set manually here */
								if (!r_core_bin_load (&r, filepath, baddr)) {
									r_config_set_i (r.config, "io.va", false);
								}
							}
