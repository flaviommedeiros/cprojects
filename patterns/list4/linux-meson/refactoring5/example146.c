#ifdef CONFIG_TDLS
if((psta->tdls_sta_state & TDLS_LINKED_STATE) && 
			(psta->htpriv.ht_option==_TRUE) &&
			(psta->htpriv.ampdu_enable==_TRUE))
		{
			DBG_871X("Recv [%s] from direc link\n", __FUNCTION__);
		}
		else
#endif //CONFIG_TDLS
		if (!pmlmeinfo->HT_enable)
		{
			return _SUCCESS;
		}
