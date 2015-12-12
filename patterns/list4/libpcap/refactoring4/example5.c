#if defined(TP_STATUS_VLAN_VALID)
if ((aux->tp_vlan_tci == 0) && !(aux->tp_status & TP_STATUS_VLAN_VALID))
#else
			if (aux->tp_vlan_tci == 0) /* this is ambigious but without the
						TP_STATUS_VLAN_VALID flag, there is
						nothing that we can do */
#endif
				continue;
