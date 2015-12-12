if(D(db)->get(D(db),
#ifdef HAVE_DB3
	       NULL,
#endif
	       &key, &value, 0) != 0) {
	dvalue.dptr = NULL;
	dvalue.dsize = 0;
    }
    else
	DBT2DATUM(&value, &dvalue);
