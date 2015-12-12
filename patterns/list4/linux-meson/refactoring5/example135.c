#ifdef CONFIG_RTL8711
if(IS_MCAST(psta->hwaddr))
	{
		ptxservq = &(psta->sta_xmitpriv.be_q); // we will use be_q to queue bc/mc frames in BCMC_stainfo
		*ppstapending = &padapter->xmitpriv.bm_pending; 
	
