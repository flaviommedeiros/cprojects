#ifdef ENABLE_SSL
if(!(options->management_flags & MF_EXTERNAL_KEY))
#endif
     errs |= check_file_access (CHKACC_FILE|CHKACC_INLINE, options->priv_key_file, R_OK,
                             "--key");
