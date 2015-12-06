int _WritePSFont(FILE *out,SplineFont *sf,enum fontformat format,int flags,
	EncMap *map, SplineFont *fullsf,int layer) {
    int err = false;

    if ( format!=ff_cid && format!=ff_ptype3 &&
	    (othersubrs[0]==NULL || othersubrs[0][0]==NULL ||
		(othersubrs[0][1]==NULL && strcmp(othersubrs[0][0],"{}")==0)))
	flags &= ~ps_flag_noflex;

    /* make sure that all reals get output with '.' for decimal points */
    locale_t tmplocale; locale_t oldlocale; // Declare temporary locale storage.
    switch_to_c_locale(&tmplocale, &oldlocale); // Switch to the C locale temporarily and cache the old locale.
    if ( (format==ff_mma || format==ff_mmb) && sf->mm!=NULL )
	sf = sf->mm->normal;
    if ( format==ff_cid )
	err = !dumpcidstuff(out,sf->subfontcnt>0?sf:sf->cidmaster,flags,map,layer);
    else {
	dumpfontdict(out,sf,format,flags,map,fullsf,layer);
	if ( format==ff_ptype0 )
	    dumptype0stuff(out,sf,map);
    }
    switch_to_old_locale(&tmplocale, &oldlocale); // Switch to the cached locale.
    if ( ferror(out) || err)
return( 0 );

#ifdef __CygWin
    /* Modern versions of windows want the execute bit set on a ttf file */
    /*  It might also be needed for a postscript font, but I haven't checked */
    /* It isn't needed on the pfb file, but is on the pfm, so this code */
    /*  isn't really useful */
    /* I've no idea what this corresponds to in windows, nor any idea on */
    /*  how to set it from the windows UI, but this seems to work */
    {
	struct stat buf;
	fstat(fileno(out),&buf);
	fchmod(fileno(out),S_IXUSR | buf.st_mode );
    }
#endif

return( true );
}
