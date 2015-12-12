#ifdef CONFIG_TDLS
if (pattrib->direct_link == _TRUE) {
			if (pattrib->qos_en)
				set_qos(&pktfile, pattrib);
		} else 
#endif
		{
			if (pqospriv->qos_option) {
				set_qos(&pktfile, pattrib);

				if (pmlmepriv->acm_mask != 0)
					pattrib->priority = qos_acm(pmlmepriv->acm_mask, pattrib->priority);
			}
		}
