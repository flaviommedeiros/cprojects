#ifndef PKTPRIO_OVERRIDE
if (PKTPRIO(pktbuf) == 0)
#endif 
		pktsetprio(pktbuf, FALSE);
