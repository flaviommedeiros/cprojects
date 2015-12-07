#if   SYM_CONF_DMA_ADDRESSING_MODE == 0
if (!np->use_dac)
			np->rv_ccntl1	|= (DDAC);
		else
			np->rv_ccntl1	|= (XTIMOD | EXTIBMV);
