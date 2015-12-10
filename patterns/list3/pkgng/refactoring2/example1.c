#ifndef NFL
if (!ps->LEVEL || !ps->simplifying)
#endif
    {
      new_phase = (LIT2SGN (lit) > 0);

      if (v->assigned)
	{
	  ps->sdflips -= ps->sdflips/FFLIPPED;

	  if (new_phase != v->phase)
	    {
	      assert (FFLIPPEDPREC >= FFLIPPED);
	      ps->sdflips += FFLIPPEDPREC / FFLIPPED;
	      ps->flips++;

	      idx = LIT2IDX (lit);
	      if (idx < ps->min_flipped)
		ps->min_flipped = idx;

              NOLOG (fprintf (ps->out, 
	                      "%sflipped %d\n",
			       ps->prefix, LIT2INT (lit)));
	    }
	}

      v->phase = new_phase;
      v->assigned = 1;
    }
