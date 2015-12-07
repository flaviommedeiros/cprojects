#ifndef	MOT_ELM
if (plc_rev != PLC_REV_SN3)
#endif	/* MOT_ELM */
		{
			/*
			 * No supernet III PLC, so set Xmit verctor and
			 * length BEFORE starting the state machine.
			 */
			if (plc_send_bits(smc,phy,3)) {
				return ;
			}
		}
