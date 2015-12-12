#if defined HAVE_BG_L_P && (SYSTEM_DIMENSIONS != 3)
if (!getenv("CLASSPATH") || !getenv("DB2INSTANCE")
		    || !getenv("VWSPATH"))
			fatal("db2profile has not been "
			      "run to setup DB2 environment");
