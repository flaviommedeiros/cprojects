#ifdef WITH_NDBCLUSTER_STORAGE_ENGINE
if (ndb_code)
      {
        if ((ndb_error_string(code, ndb_string, sizeof(ndb_string)) < 0) &&
            (ndbd_exit_string(code, ndb_string, sizeof(ndb_string)) < 0) &&
            (mgmapi_error_string(code, ndb_string, sizeof(ndb_string)) < 0))
	{
          msg= 0;
	}
	else
	  msg= ndb_string;
        if (msg)
        {
          if (verbose)
            printf("NDB error code %3d: %s\n",code,msg);
          else
            puts(msg);
        }
        else
        {
	  fprintf(stderr,"Illegal ndb error code: %d\n",code);
          error= 1;
        }
        found= 1;
        msg= 0;
      }
      else
#endif
	msg = strerror(code);
