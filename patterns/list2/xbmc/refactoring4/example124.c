#ifdef USE_DSP_EFFECT
if(opt_surround_chorus && voice[i].chorus_link != i)
#else
	    if((channel[c].chorus_level || opt_surround_chorus) &&
	       voice[i].chorus_link != i)
#endif
	    {
		int v1, v2;

		if(i >= voice[i].chorus_link)
		    /* `i' is not base chorus voice.
		     *  This sub voice is already updated.
		     */
		    continue;

		v1 = i;				/* base voice */
		v2 = voice[i].chorus_link;	/* sub voice (detuned) */

		if(opt_surround_chorus) /* Surround chorus mode by Eric. */
		{
		    int panlevel;

		    if (!pan) pan = 1;	/* make hard left be 1 instead of 0 */
		    panlevel = 63;
		    if (pan - panlevel < 1) panlevel = pan - 1;
		    if (pan + panlevel > 127) panlevel = 127 - pan;
		    voice[v1].panning = pan - panlevel;
		    voice[v2].panning = pan + panlevel;
		}
		else
		{
		    voice[v1].panning = pan;
		    if(pan > 60 && pan < 68) /* PANNED_CENTER */
			voice[v2].panning =
			    64 + int_rand(40) - 20; /* 64 +- rand(20) */
		    else if(pan < CHORUS_OPPOSITE_THRESHOLD)
			voice[v2].panning = 127;
		    else if(pan > 127 - CHORUS_OPPOSITE_THRESHOLD)
			voice[v2].panning = 0;
		    else
			voice[v2].panning = (pan < 64 ? 0 : 127);
		}
		recompute_amp(v2);
		apply_envelope_to_amp(v2);
		/* v1 == i, so v1 will be updated next */
	    }
	    else
		voice[i].panning = pan;
