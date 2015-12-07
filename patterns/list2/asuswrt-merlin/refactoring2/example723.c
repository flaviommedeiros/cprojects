#ifdef PECULIAR_486
if (!
				    ((tmp.sigh == 0x00100000) && (tmp.sigl == 0)
				     && (st0_ptr->sigl & 0x000007ff)))
#endif /* PECULIAR_486 */
				{
					EXCEPTION(EX_Underflow);
					/* This is a special case: see sec 16.2.5.1 of
					   the 80486 book */
					if (!(control_word & CW_Underflow))
						return 0;
				}
