#ifdef CONFIG_TDLS
if(pattrib->direct_link == _TRUE){
				//TDLS data transfer, ToDS=0, FrDs=0
				_rtw_memcpy(pwlanhdr->addr1, pattrib->dst, ETH_ALEN);
				_rtw_memcpy(pwlanhdr->addr2, pattrib->src, ETH_ALEN);
				_rtw_memcpy(pwlanhdr->addr3, get_bssid(pmlmepriv), ETH_ALEN);

				if (pattrib->qos_en)
					qos_option = _TRUE;
			} 
			else
#endif //CONFIG_TDLS
			{
				//to_ds = 1, fr_ds = 0;
				// 1.Data transfer to AP
				// 2.Arp pkt will relayed by AP
				SetToDs(fctrl);							
				_rtw_memcpy(pwlanhdr->addr1, get_bssid(pmlmepriv), ETH_ALEN);
				_rtw_memcpy(pwlanhdr->addr2, pattrib->ta, ETH_ALEN);
				_rtw_memcpy(pwlanhdr->addr3, pattrib->dst, ETH_ALEN);

				if (pqospriv->qos_option)
					qos_option = _TRUE;
			}
