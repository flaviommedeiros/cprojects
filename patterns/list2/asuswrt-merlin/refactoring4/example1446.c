#ifdef POWERPC_LE_PE
if (! sub->output_has_begun && !ppc_do_last(sub))
#else
	      if (! sub->output_has_begun)
#endif
		{
		  if (! _bfd_coff_link_input_bfd (&finfo, sub))
		    goto error_return;
		  sub->output_has_begun = TRUE;
		}
