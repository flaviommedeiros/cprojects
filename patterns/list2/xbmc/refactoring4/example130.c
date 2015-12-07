#ifdef __BIG_ENDIAN__
if (((struct mach_header *)module)->magic == MH_MAGIC)
#else
    if (((struct mach_header *)module)->magic == MH_CIGAM)
#endif
  	{
  	    if (ltdl_NSIsSymbolNameDefinedInImage && ltdl_NSLookupSymbolInImage)
  	    {
  	    	mh=module;
			if (ltdl_NSIsSymbolNameDefinedInImage((struct mach_header*)module,symbol))
			{
				nssym = ltdl_NSLookupSymbolInImage((struct mach_header*)module,
											symbol,
											NSLOOKUPSYMBOLINIMAGE_OPTION_BIND_NOW
											| NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR
											);
			}
	    }

  	}
  else {
	nssym = NSLookupSymbolInModule(module, symbol);
	}
