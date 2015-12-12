#if (FLASHEND > 0xFFFF)
if ((uint16_t)(PageAddress >> 8) == COMMAND_STARTAPPLICATION)
			#else
			if (PageAddress == COMMAND_STARTAPPLICATION)
			#endif
			{
				RunBootloader = false;
			}
			else
			{
				/* Erase the given FLASH page, ready to be programmed */
				boot_page_erase(PageAddress);
				boot_spm_busy_wait();

				/* Write each of the FLASH page's bytes in sequence */
				for (uint8_t PageWord = 0; PageWord < (SPM_PAGESIZE / 2); PageWord++)
				{
					/* Check if endpoint is empty - if so clear it and wait until ready for next packet */
					if (!(Endpoint_BytesInEndpoint()))
					{
						Endpoint_ClearOUT();
						while (!(Endpoint_IsOUTReceived()));
					}

					/* Write the next data word to the FLASH page */
					boot_page_fill(PageAddress + ((uint16_t)PageWord << 1), Endpoint_Read_16_LE());
				}

				/* Write the filled FLASH page to memory */
				boot_page_write(PageAddress);
				boot_spm_busy_wait();

				/* Re-enable RWW section */
				boot_rww_enable();
			}
