#ifndef _NO_LIBCAIRO
if ( GDrawHasCairo(cv->v)&gc_alpha ) {
		mi->ti.checked = cv->snapoutlines;
		mi->ti.disabled = false;
	    } else
#endif
	    {
		mi->ti.checked = true;
		mi->ti.disabled = true;
	    }
