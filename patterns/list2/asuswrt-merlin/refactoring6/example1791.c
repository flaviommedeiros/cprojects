if (errno == ENOSYS
#if defined(ENOTSUP)
				|| errno == ENOTSUP) {
#else
				) {
#endif
				set_store_dos_attributes(SNUM(conn), False);
			}
