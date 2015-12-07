if ((scc->kiss.fulldup == KISS_DUPLEX_HALF) &&
#ifndef CONFIG_SCC_TRXECHO
			    scc->kiss.softdcd)
#else
			    1
