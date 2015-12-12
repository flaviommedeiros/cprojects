if ((ns == NW_NS_DOS)
#ifdef CONFIG_NCPFS_OS2_NS
		|| ((ns == NW_NS_OS2) && (nscreator == NW_NS_DOS))
#endif /* CONFIG_NCPFS_OS2_NS */
	   )
		return 0;
