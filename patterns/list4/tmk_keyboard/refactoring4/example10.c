#if (FLASHEND > 0xFFFF)
if (pgm_read_byte_far(CurrFlashAddress) != 0xFF)
			#else
			if (pgm_read_byte(CurrFlashAddress) != 0xFF)
			#endif
			{
				/* Save the location of the first non-blank byte for response back to the host */
				Flash64KBPage = (CurrFlashAddress >> 16);
				StartAddr     = CurrFlashAddress;

				/* Set state and status variables to the appropriate error values */
				DFU_State  = dfuERROR;
				DFU_Status = errCHECK_ERASED;

				break;
			}
