#ifdef HAVE_GETOPT_LONG
if (!one_opt(option, arg, daemon->namebuff, _("try --help"), 1, 0))
#else 
	    if (!one_opt(option, arg, daemon->namebuff, _("try -w"), 1, 0)) 
#endif  
	    die(_("bad command line options: %s"), daemon->namebuff, EC_BADCONF);
