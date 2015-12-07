#ifdef MANAGMENT_EXTERNAL_KEY
if((o->management_flags & MF_EXTERNAL_KEY))
	SHOW_PARM ("priv_key_file","EXTERNAL_PRIVATE_KEY","%s");
  else
#endif
  SHOW_STR (priv_key_file);
