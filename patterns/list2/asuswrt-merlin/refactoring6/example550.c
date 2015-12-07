if (ks->state >= S_ACTIVE
	      && ks->authenticated
#ifdef ENABLE_DEF_AUTH
	      && !ks->auth_deferred
#endif
	      )
	    {
	      if (!ks_select)
		ks_select = ks;
	      if (now >= ks->auth_deferred_expire)
		{
		  ks_select = ks;
		  break;
		}
	    }
