if (errno == ENOSYS
#if defined(ENOTSUP)
				|| errno == ENOTSUP) {
#else
				) {
#endif
				DEBUG(1,("set_ea_dos_attributes: Cannot set "
					 "attribute EA on file %s: Error = %s\n",
					 smb_fname_str_dbg(smb_fname),
					 strerror(errno) ));
				set_store_dos_attributes(SNUM(conn), False);
			}
