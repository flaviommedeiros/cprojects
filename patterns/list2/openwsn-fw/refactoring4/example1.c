#if(defined MCU_MK20D5) || (defined MCU_MK20D7) || (defined MCU_MK40D7)
if(PORTC_ISFR & (1<<1))
	#else
		if(PORTC_ISFR & (1<<5))
	#endif	
		{
			kbi_stat |= 0x02; 				/* Update the kbi state */
			
			/* Clear the bit by writing a 1 to it */
		#if(defined MCU_MK20D5) || (defined MCU_MK20D7) || (defined MCU_MK40D7)
			PORTC_ISFR |=(1<<1);
		#else
			PORTC_ISFR |=(1<<5);
		#endif							
		}
