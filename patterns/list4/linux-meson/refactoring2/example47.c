#ifdef CONFIG_PREALLOC_RX_SKB_BUFFER
if(rtw_free_skb_premem(precvbuf->pskb)!=0)
#endif
		rtw_skb_free(precvbuf->pskb);
