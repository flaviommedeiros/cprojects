#ifdef CONFIG_TDLS
if( !(psta->tdls_sta_state & TDLS_LINKED_STATE) )
#endif //CONFIG_TDLS
	pstapriv->sta_dz_bitmap |= BIT(psta->aid);
