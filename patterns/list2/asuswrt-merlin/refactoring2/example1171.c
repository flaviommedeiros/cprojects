#ifdef PECULIAR_486
if ( !((tmp.sigl == 0x00800000) &&
		  ((st0_ptr->sigh & 0x000000ff) || st0_ptr->sigl)) )
#endif /* PECULIAR_486 */
		{
		  EXCEPTION(EX_Underflow);
		  /* This is a special case: see sec 16.2.5.1 of
		     the 80486 book */
		  if ( !(control_word & CW_Underflow) )
		    return 0;
		}
