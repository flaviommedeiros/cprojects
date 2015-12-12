return sprintf(page,"%4sBursts: TX"
#if !defined(CONFIG_ATM_ENI_BURST_TX_16W) && \
    !defined(CONFIG_ATM_ENI_BURST_TX_8W) && \
    !defined(CONFIG_ATM_ENI_BURST_TX_4W) && \
    !defined(CONFIG_ATM_ENI_BURST_TX_2W)
		    " none"
#endif
#ifdef CONFIG_ATM_ENI_BURST_TX_16W
		    " 16W"
#endif
#ifdef CONFIG_ATM_ENI_BURST_TX_8W
		    " 8W"
#endif
#ifdef CONFIG_ATM_ENI_BURST_TX_4W
		    " 4W"
#endif
#ifdef CONFIG_ATM_ENI_BURST_TX_2W
		    " 2W"
#endif
		    ", RX"
#if !defined(CONFIG_ATM_ENI_BURST_RX_16W) && \
    !defined(CONFIG_ATM_ENI_BURST_RX_8W) && \
    !defined(CONFIG_ATM_ENI_BURST_RX_4W) && \
    !defined(CONFIG_ATM_ENI_BURST_RX_2W)
		    " none"
#endif
#ifdef CONFIG_ATM_ENI_BURST_RX_16W
		    " 16W"
#endif
#ifdef CONFIG_ATM_ENI_BURST_RX_8W
		    " 8W"
#endif
#ifdef CONFIG_ATM_ENI_BURST_RX_4W
		    " 4W"
#endif
#ifdef CONFIG_ATM_ENI_BURST_RX_2W
		    " 2W"
#endif
#ifndef CONFIG_ATM_ENI_TUNE_BURST
		    " (default)"
#endif
		    "\n","");
