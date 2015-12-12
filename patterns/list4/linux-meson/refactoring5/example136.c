#ifdef CONFIG_TDLS
if((psta->tdls_sta_state & TDLS_LINKED_STATE) && (psta->dot118021XPrivacy==_AES_))
		{
			pattrib->encrypt=psta->dot118021XPrivacy;
		}
		else
#endif //CONFIG_TDLS
		GET_ENCRY_ALGO(psecuritypriv, psta, pattrib->encrypt, IS_MCAST(pattrib->ra));
