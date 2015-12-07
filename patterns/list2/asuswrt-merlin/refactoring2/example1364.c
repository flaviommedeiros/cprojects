#ifndef CONFIG_SCC_TRXECHO
if (scc->kiss.softdcd)
#endif
			{
				or(scc,R15, scc->kiss.softdcd? SYNCIE:DCDIE);
				start_hunt(scc);
			}
